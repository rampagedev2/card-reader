/**
 * @file main.c — Card reader application (bare-metal, no HAL)
 *
 * Flow: init → poll RC522 → on UID update MSC files + ECC sign + beep
 */
#include "bsp.h"
#include "board.h"
#include "mfrc522.h"
#include "ecc_p256.h"
#include "usb_msc.h"
#include <string.h>

static void hash_uid(const mfrc522_uid_t *uid, uint8_t out[32])
{
    uint32_t i;
    uint8_t n = uid->size ? uid->size : 1U;
    memset(out, 0, 32);
    for (i = 0; i < uid->size && i < 32U; i++)
        out[i] = uid->uid[i];
    for (; i < 32U; i++)
        out[i] = (uint8_t)(0xA5u ^ (uint8_t)i ^ out[i % n]);
}

int main(void)
{
    mfrc522_uid_t uid;
    uint8_t hash[32];
    uint8_t sig[64];
    char line[48];
    uint32_t last_poll = 0;
    uint8_t last_uid[10];
    uint8_t last_len = 0;

    /* SystemInit already ran from Reset_Handler */
    board_init();
    ecc_init();
    (void)ecc_load_or_create_key();
    mfrc522_init();
    usb_msc_init();

    led_status(1);
    if (mfrc522_pcd_is_ready())
        buzzer_ok();
    else
        buzzer_err();

    for (;;) {
        usb_msc_poll();

        if ((millis() - last_poll) < 50U)
            continue;
        last_poll = millis();

        if (!mfrc522_picc_is_new_card_present()) {
            led_rf(0);
            continue;
        }

        if (mfrc522_picc_read_card_serial(&uid) != MFRC522_OK) {
            buzzer_err();
            continue;
        }

        /* Debounce same card */
        if (last_len == uid.size && memcmp(last_uid, uid.uid, uid.size) == 0) {
            mfrc522_picc_halt();
            continue;
        }
        memcpy(last_uid, uid.uid, uid.size);
        last_len = uid.size;

        led_rf(1);
        usb_msc_set_uid(uid.uid, uid.size);

        {
            uint8_t i, n = 0;
            static const char hex[] = "0123456789ABCDEF";
            line[n++] = '0';
            line[n++] = ',';
            for (i = 0; i < uid.size && n < 40U; i++) {
                line[n++] = hex[uid.uid[i] >> 4];
                line[n++] = hex[uid.uid[i] & 0xFU];
            }
            line[n] = 0;
            usb_msc_append_log(line);
        }

        hash_uid(&uid, hash);
        if (ecc_sign(hash, sig))
            usb_msc_set_signature(sig, 64);

        buzzer_ok();
        mfrc522_picc_halt();
        delay_ms(300);
        led_rf(0);
    }
}
