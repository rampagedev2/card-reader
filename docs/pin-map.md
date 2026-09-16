# Pin Map — GD32F407VET6

Package: LQFP-100. RFID via **RC522 module** (not discrete chip).

## Power / reset / clock

| Pin | Net | Notes |
|-----|-----|-------|
| 11, 19, 28, 50, 75, 100 | VDD | 3V3, 100 nF each + 10 uF bulk |
| 12, 18, 27, 49, 74, 99 | VSS | GND |
| 22 | VDDA | 3V3 via ferrite + 1 uF / 100 nF |
| 21 | VSSA | GND |
| 14 | NRST | 10k pull-up, 100 nF to GND |
| 23 | OSC_IN | 8 MHz X1 |
| 24 | OSC_OUT | 8 MHz X1 |
| 94 | BOOT0 | 10k to GND |

## USB

| Pin | Net | Function |
|-----|-----|----------|
| 70 | PA11 | USB_DM |
| 71 | PA12 | USB_DP |

## SWD

| Pin | Net | Function |
|-----|-----|----------|
| 72 | PA13 | SWDIO |
| 76 | PA14 | SWCLK |

## SPI1 → RC522 module (J3)

| MCU pin | Net | Module pin (typical) |
|---------|-----|----------------------|
| 3V3 | 3V3 | 3.3V |
| GND | GND | GND |
| PA5 | SPI1_SCK | SCK |
| PA6 | SPI1_MISO | MISO |
| PA7 | SPI1_MOSI | MOSI |
| PA4 | SPI1_NSS | SDA |
| PC4 | RFID_RST | RST |
| PC5 | RFID_IRQ | IRQ (optional) |

**Important:** Power module from **3.3V only** (not 5V).

## User I/O

| Pin | Net | Function |
|-----|-----|----------|
| PB0 | BUZZER_PWM | TIM PWM |
| PB1 | LED_STATUS | Green |
| PB2 | LED_RF | Blue |
