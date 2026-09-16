# Pin Map — GD32F407VET6

Package: LQFP-100. Only used pins listed.

## Power / reset / clock

| Pin | Net | Notes |
|-----|-----|-------|
| 11, 19, 28, 50, 75, 100 | VDD | 3V3, 100 nF each + 10 µF bulk |
| 12, 18, 27, 49, 74, 99 | VSS | GND |
| 22 | VDDA | 3V3 via ferrite + 1 µF / 100 nF |
| 21 | VSSA | GND |
| 14 | NRST | 10 kΩ pull-up, 100 nF to GND, SWD reset |
| 23 | OSC_IN | 8 MHz X1 |
| 24 | OSC_OUT | 8 MHz X1 |
| 94 | BOOT0 | 10 kΩ to GND |

## USB

| Pin | Net | Function |
|-----|-----|----------|
| 70 | PA11 | USB_DM |
| 71 | PA12 | USB_DP |

## SWD debug

| Pin | Net | Function |
|-----|-----|----------|
| 72 | PA13 | SWDIO |
| 76 | PA14 | SWCLK |
| 14 | NRST | Reset |

## SPI1 → MFRC522

| Pin | Net | MFRC522 |
|-----|-----|---------|
| 51 | PA5 | SCK |
| 52 | PA6 | MISO |
| 53 | PA7 | MOSI |
| 54 | PA4 | NSS (SDA) |
| 55 | PC4 | RST |
| 56 | PC5 | IRQ |

## User I/O

| Pin | Net | Function |
|-----|-----|----------|
| 57 | PB0 | BUZZER_PWM (TIM3_CH3) |
| 58 | PB1 | LED_STATUS (green) |
| 59 | PB2 | LED_RF (blue, activity) |

## Not used (removed)

SPI2 / W25Q128 pins (PB12–PB15) are free — no external MSC flash.

## Reserved / future

| Pin | Net | Idea |
|-----|-----|------|
| 60 | PE7 | UART1_TX debug |
| 61 | PE8 | UART1_RX debug |
| 40 | PC13 | User button (optional) |
