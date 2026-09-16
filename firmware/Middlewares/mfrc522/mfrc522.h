#ifndef MFRC522_H
#define MFRC522_H

#include <stdint.h>

#define MFRC522_OK           0
#define MFRC522_ERR          1
#define MFRC522_TIMEOUT      2
#define MFRC522_UID_MAX      10

typedef struct {
    uint8_t size;
    uint8_t uid[MFRC522_UID_MAX];
    uint8_t sak;
} mfrc522_uid_t;

void mfrc522_init(void);
uint8_t mfrc522_pcd_is_ready(void);
uint8_t mfrc522_picc_is_new_card_present(void);
uint8_t mfrc522_picc_read_card_serial(mfrc522_uid_t *uid);
void mfrc522_picc_halt(void);

#endif
