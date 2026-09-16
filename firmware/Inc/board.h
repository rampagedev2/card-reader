#ifndef BOARD_H
#define BOARD_H

/* Pin map — GD32F407VET6 + RC522 module (see docs/pin-map.md) */

#define LED_STATUS_PORT   GPIOB
#define LED_STATUS_PIN    1U   /* PB1 green */
#define LED_RF_PORT       GPIOB
#define LED_RF_PIN        2U   /* PB2 blue */

#define BUZZER_PORT       GPIOB
#define BUZZER_PIN        0U   /* PB0 TIMER2_CH2 AF2 */

#define RFID_NSS_PORT     GPIOA
#define RFID_NSS_PIN      4U   /* PA4 */
#define RFID_SCK_PORT     GPIOA
#define RFID_SCK_PIN      5U
#define RFID_MISO_PORT    GPIOA
#define RFID_MISO_PIN     6U
#define RFID_MOSI_PORT    GPIOA
#define RFID_MOSI_PIN     7U
#define RFID_RST_PORT     GPIOC
#define RFID_RST_PIN      4U   /* PC4 */
#define RFID_IRQ_PORT     GPIOC
#define RFID_IRQ_PIN      5U   /* PC5 */

#define USB_DM_PIN        11U  /* PA11 */
#define USB_DP_PIN        12U  /* PA12 */

#endif
