/**
 * @file mfrc522.c — MFRC522 over SPI (ISO14443A UID) — no HAL
 */
#include "mfrc522.h"
#include "spi_bus.h"
#include "board.h"
#include "gd32f407_regs.h"
#include "bsp.h"

#define REG_COMMAND       0x01
#define REG_COMIEN        0x02
#define REG_DIVIEN        0x03
#define REG_COMIRQ        0x04
#define REG_ERROR         0x06
#define REG_STATUS2       0x08
#define REG_FIFODATA      0x09
#define REG_FIFOLEVEL     0x0A
#define REG_CONTROL       0x0C
#define REG_BITFRAMING    0x0D
#define REG_COLL          0x0E
#define REG_MODE          0x11
#define REG_TXMODE        0x12
#define REG_RXMODE        0x13
#define REG_TXCONTROL     0x14
#define REG_TXASK         0x15
#define REG_CRCRESULT_H   0x21
#define REG_CRCRESULT_L   0x22
#define REG_MODWIDTH      0x24
#define REG_RFCFG         0x26
#define REG_TMODE         0x2A
#define REG_TPRESCALER    0x2B
#define REG_TRELOAD_H     0x2C
#define REG_TRELOAD_L     0x2D
#define REG_VERSION       0x37

#define PCD_IDLE          0x00
#define PCD_CALCCRC       0x03
#define PCD_TRANSCEIVE    0x0C
#define PCD_SOFTRESET     0x0F

#define PICC_REQA         0x26
#define PICC_ANTICOLL     0x93

static void pcd_write(uint8_t reg, uint8_t val)
{
    spi0_nss(0);
    (void)spi0_xfer((uint8_t)((reg << 1) & 0x7EU));
    (void)spi0_xfer(val);
    spi0_nss(1);
}

static uint8_t pcd_read(uint8_t reg)
{
    uint8_t v;
    spi0_nss(0);
    (void)spi0_xfer((uint8_t)(((reg << 1) & 0x7EU) | 0x80U));
    v = spi0_xfer(0);
    spi0_nss(1);
    return v;
}

static void pcd_set_bits(uint8_t reg, uint8_t mask)
{
    pcd_write(reg, (uint8_t)(pcd_read(reg) | mask));
}

static void pcd_clear_bits(uint8_t reg, uint8_t mask)
{
    pcd_write(reg, (uint8_t)(pcd_read(reg) & (uint8_t)~mask));
}

static void pcd_antenna_on(void)
{
    uint8_t v = pcd_read(REG_TXCONTROL);
    if ((v & 0x03U) != 0x03U)
        pcd_write(REG_TXCONTROL, (uint8_t)(v | 0x03U));
}

static void pcd_reset(void)
{
    RFID_RST_PORT->BOP = (1U << (RFID_RST_PIN + 16U));
    delay_ms(2);
    RFID_RST_PORT->BOP = (1U << RFID_RST_PIN);
    delay_ms(50);
    pcd_write(REG_COMMAND, PCD_SOFTRESET);
    delay_ms(50);
    while (pcd_read(REG_COMMAND) & (1U << 4)) {
    }
}

void mfrc522_init(void)
{
    spi0_init();
    pcd_reset();
    pcd_write(REG_TMODE, 0x80);
    pcd_write(REG_TPRESCALER, 0xA9);
    pcd_write(REG_TRELOAD_H, 0x03);
    pcd_write(REG_TRELOAD_L, 0xE8);
    pcd_write(REG_TXASK, 0x40);
    pcd_write(REG_MODE, 0x3D);
    pcd_antenna_on();
}

uint8_t mfrc522_pcd_is_ready(void)
{
    uint8_t v = pcd_read(REG_VERSION);
    return (v == 0x91U || v == 0x92U || v == 0x88U) ? 1U : 0U;
}

static uint8_t pcd_transceive(uint8_t *send, uint8_t send_len,
                              uint8_t *back, uint8_t *back_len, uint8_t *valid_bits)
{
    uint8_t i, n, last_bits;
    uint16_t wait = 2000;

    pcd_write(REG_COMIEN, 0x80);
    pcd_write(REG_COMIRQ, 0x7F);
    pcd_set_bits(REG_FIFOLEVEL, 0x80);
    pcd_write(REG_COMMAND, PCD_IDLE);

    for (i = 0; i < send_len; i++)
        pcd_write(REG_FIFODATA, send[i]);

    pcd_write(REG_COMMAND, PCD_TRANSCEIVE);
    pcd_set_bits(REG_BITFRAMING, 0x80);

    while (wait--) {
        n = pcd_read(REG_COMIRQ);
        if (n & 0x30U)
            break;
        if (n & 0x01U)
            return MFRC522_TIMEOUT;
    }
    pcd_clear_bits(REG_BITFRAMING, 0x80);

    if (pcd_read(REG_ERROR) & 0x13U)
        return MFRC522_ERR;

    n = pcd_read(REG_FIFOLEVEL);
    last_bits = (uint8_t)(pcd_read(REG_CONTROL) & 0x07U);
    if (valid_bits)
        *valid_bits = last_bits;
    if (n > *back_len)
        n = *back_len;
    *back_len = n;
    for (i = 0; i < n; i++)
        back[i] = pcd_read(REG_FIFODATA);
    return MFRC522_OK;
}

uint8_t mfrc522_picc_is_new_card_present(void)
{
    uint8_t buf[2];
    uint8_t len = 2;
    uint8_t vb = 7;
    uint8_t cmd = PICC_REQA;
    pcd_write(REG_BITFRAMING, 0x07);
    if (pcd_transceive(&cmd, 1, buf, &len, &vb) != MFRC522_OK)
        return 0;
    return (len == 2U || (len == 1U && vb)) ? 1U : 0U;
}

uint8_t mfrc522_picc_read_card_serial(mfrc522_uid_t *uid)
{
    uint8_t buf[5];
    uint8_t send[2];
    uint8_t len = 5;
    uint8_t vb = 0;
    uint8_t i, bcc;

    send[0] = PICC_ANTICOLL;
    send[1] = 0x20;
    pcd_write(REG_BITFRAMING, 0x00);
    pcd_write(REG_COLL, 0x80);
    if (pcd_transceive(send, 2, buf, &len, &vb) != MFRC522_OK || len != 5U)
        return MFRC522_ERR;

    bcc = 0;
    for (i = 0; i < 4U; i++)
        bcc ^= buf[i];
    if (bcc != buf[4])
        return MFRC522_ERR;

    uid->size = 4;
    for (i = 0; i < 4U; i++)
        uid->uid[i] = buf[i];
    uid->sak = 0;
    return MFRC522_OK;
}

void mfrc522_picc_halt(void)
{
    /* Minimal: soft idle */
    pcd_write(REG_COMMAND, PCD_IDLE);
}
