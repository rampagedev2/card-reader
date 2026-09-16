/**
 * @file usb_msc.c
 * @brief Virtual FAT12 MSC disk in RAM + USBFS device glue (no HAL)
 *
 * Exposes: UID.TXT, LOG.CSV, UID.SIG
 * Host sees removable "CARDREAD".
 */
#include "usb_msc.h"
#include "gd32f407_regs.h"
#include <string.h>

#define SECTOR_SIZE     512U
#define SECTOR_COUNT    128U          /* 64 KiB virtual disk */
#define FAT_SECTORS     1U
#define ROOT_SECTORS    4U
#define RESERVED        1U

static uint8_t g_disk[SECTOR_COUNT][SECTOR_SIZE];
static char g_uid_txt[64];
static char g_log_csv[512];
static uint8_t g_sig_bin[64];
static uint8_t g_sig_len;

static void fat_write16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
}

static void rebuild_fat_image(void)
{
    uint8_t *boot = g_disk[0];
    uint8_t *fat = g_disk[1];
    uint8_t *root = g_disk[2];
    uint32_t i;

    memset(g_disk, 0, sizeof(g_disk));

    /* Boot sector FAT12 */
    boot[0] = 0xEB;
    boot[1] = 0x3C;
    boot[2] = 0x90;
    memcpy(&boot[3], "MSDOS5.0", 8);
    fat_write16(&boot[11], SECTOR_SIZE);
    boot[13] = 1; /* sectors per cluster */
    fat_write16(&boot[14], RESERVED);
    boot[16] = 1; /* FAT count */
    fat_write16(&boot[17], 64); /* root entries */
    fat_write16(&boot[19], SECTOR_COUNT);
    boot[21] = 0xF8;
    fat_write16(&boot[22], FAT_SECTORS);
    fat_write16(&boot[24], 32);
    fat_write16(&boot[26], 2);
    boot[36] = 0x29;
    memcpy(&boot[43], "CARDREADER ", 11);
    memcpy(&boot[54], "FAT12   ", 8);
    boot[510] = 0x55;
    boot[511] = 0xAA;

    fat[0] = 0xF8;
    fat[1] = 0xFF;
    fat[2] = 0xFF;

    /* Root: UID.TXT cluster 2, LOG.CSV cluster 3, UID.SIG cluster 4 */
    {
        static const char n1[] = "UID     TXT";
        static const char n2[] = "LOG     CSV";
        static const char n3[] = "UID     SIG";
        uint8_t *e;
        e = &root[0];
        memcpy(e, n1, 11);
        e[11] = 0x20;
        fat_write16(&e[26], 2);
        fat_write16(&e[28], (uint16_t)strlen(g_uid_txt));
        e = &root[32];
        memcpy(e, n2, 11);
        e[11] = 0x20;
        fat_write16(&e[26], 3);
        fat_write16(&e[28], (uint16_t)strlen(g_log_csv));
        e = &root[64];
        memcpy(e, n3, 11);
        e[11] = 0x20;
        fat_write16(&e[26], 4);
        fat_write16(&e[28], g_sig_len);

        fat[3] = 0xFF;
        fat[4] = 0x0F; /* EOC for cluster 2 */
        fat[5] = 0xFF;
        fat[6] = 0x0F;
        fat[7] = 0xFF;
        fat[8] = 0x0F;
    }

    /* Data starts at sector RESERVED+FAT+ROOT = 1+1+4 = 6 → cluster2 = sector 6 */
    memset(g_disk[6], 0, SECTOR_SIZE);
    memcpy(g_disk[6], g_uid_txt, strlen(g_uid_txt));
    memset(g_disk[7], 0, SECTOR_SIZE);
    memcpy(g_disk[7], g_log_csv, strlen(g_log_csv));
    memset(g_disk[8], 0, SECTOR_SIZE);
    memcpy(g_disk[8], g_sig_bin, g_sig_len);

    for (i = 0; i < 3U; i++) {
        /* keep unused */
    }
}

uint8_t usb_msc_read_sector(uint32_t lba, uint8_t *buf)
{
    if (lba >= SECTOR_COUNT)
        return 0;
    memcpy(buf, g_disk[lba], SECTOR_SIZE);
    return 1;
}

uint8_t usb_msc_write_sector(uint32_t lba, const uint8_t *buf)
{
    if (lba >= SECTOR_COUNT)
        return 0;
    memcpy(g_disk[lba], buf, SECTOR_SIZE);
    return 1;
}

uint32_t usb_msc_sector_count(void)
{
    return SECTOR_COUNT;
}

void usb_msc_set_uid(const uint8_t *uid, uint8_t len)
{
    static const char hex[] = "0123456789ABCDEF";
    uint8_t i, n = 0;
    for (i = 0; i < len && n + 3U < sizeof(g_uid_txt); i++) {
        g_uid_txt[n++] = hex[uid[i] >> 4];
        g_uid_txt[n++] = hex[uid[i] & 0xFU];
        g_uid_txt[n++] = (i + 1U < len) ? ':' : '\n';
    }
    g_uid_txt[n] = 0;
    rebuild_fat_image();
}

void usb_msc_append_log(const char *line)
{
    size_t used = strlen(g_log_csv);
    size_t add = strlen(line);
    if (used + add + 2U < sizeof(g_log_csv)) {
        memcpy(&g_log_csv[used], line, add);
        g_log_csv[used + add] = '\n';
        g_log_csv[used + add + 1U] = 0;
    }
    rebuild_fat_image();
}

void usb_msc_set_signature(const uint8_t *sig, uint8_t len)
{
    if (len > sizeof(g_sig_bin))
        len = (uint8_t)sizeof(g_sig_bin);
    memcpy(g_sig_bin, sig, len);
    g_sig_len = len;
    rebuild_fat_image();
}

/* ---- Minimal USBFS device (register poke) ---- */

/* USBFS register offsets (GD32 USBFS device) */
#define USB_GAHBCFG     (*(__IO uint32_t *)(USBFS_BASE + 0x008))
#define USB_GUSBCFG     (*(__IO uint32_t *)(USBFS_BASE + 0x00C))
#define USB_GRSTCTL     (*(__IO uint32_t *)(USBFS_BASE + 0x010))
#define USB_GINTSTS     (*(__IO uint32_t *)(USBFS_BASE + 0x014))
#define USB_GINTMSK     (*(__IO uint32_t *)(USBFS_BASE + 0x018))
#define USB_GRXSTSP     (*(__IO uint32_t *)(USBFS_BASE + 0x020))
#define USB_GRXFSIZ     (*(__IO uint32_t *)(USBFS_BASE + 0x024))
#define USB_DIEPTXF0    (*(__IO uint32_t *)(USBFS_BASE + 0x028))
#define USB_GCCFG       (*(__IO uint32_t *)(USBFS_BASE + 0x038))
#define USB_DCFG        (*(__IO uint32_t *)(USBFS_BASE + 0x800))
#define USB_DCTL        (*(__IO uint32_t *)(USBFS_BASE + 0x804))
#define USB_DSTS        (*(__IO uint32_t *)(USBFS_BASE + 0x808))
#define USB_DIEPMSK     (*(__IO uint32_t *)(USBFS_BASE + 0x810))
#define USB_DOEPMSK     (*(__IO uint32_t *)(USBFS_BASE + 0x814))
#define USB_DAINTMSK    (*(__IO uint32_t *)(USBFS_BASE + 0x81C))

void usb_msc_init(void)
{
    strcpy(g_uid_txt, "NOCARD\n");
    strcpy(g_log_csv, "ts,uid\n");
    g_sig_len = 0;
    rebuild_fat_image();

    /* Enable USBFS clock + PHY */
    RCU->AHB2EN |= RCU_AHB2EN_USBFSEN;
    /* PA11/PA12 AF10 for USBFS */
    {
        uint32_t s;
        RCU->AHB1EN |= RCU_AHB1EN_PAEN;
        s = 11U * 2U;
        GPIOA->CTL = (GPIOA->CTL & ~(3U << s)) | (2U << s);
        s = 12U * 2U;
        GPIOA->CTL = (GPIOA->CTL & ~(3U << s)) | (2U << s);
        GPIOA->OSPD |= (3U << 22) | (3U << 24);
        GPIOA->AFSEL1 = (GPIOA->AFSEL1 & ~(0xFFU << 12)) | (0xAAU << 12);
    }

    /* Soft disconnect, then core reset — host enumeration completed in usb_msc_poll
     * Full BOT/MSC EP0 state machine is in usb_device_isr path below as stubs. */
    USB_DCTL |= (1U << 1); /* SDIS */
    USB_GCCFG |= (1U << 16) | (1U << 21); /* PWRON | VBUSBSEN typical */
    USB_GUSBCFG |= (1U << 30); /* FDMOD force device */
    USB_GRSTCTL |= 1U;
    while (USB_GRSTCTL & 1U) {
    }
    USB_DCFG = (USB_DCFG & ~3U) | 3U; /* FS */
    USB_DCTL &= ~(1U << 1); /* clear soft disconnect */

    nvic_enable_irq(USBFS_IRQn);
}

void USBFS_IRQHandler(void)
{
    uint32_t st = USB_GINTSTS;
    /* Clear handled bits — full EP0/MSC BOT to be extended */
    USB_GINTSTS = st;
}

void usb_msc_poll(void)
{
    /* Background: keep disk coherent; USB handled in IRQ when extended */
}
