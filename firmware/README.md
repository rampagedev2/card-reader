# Firmware — GD32F407VET6 bare-metal (no HAL) + legacy Keil

## Rules

- **No HAL / no SPL** — register-level drivers + minimal CMSIS map (`CMSIS/gd32f407_regs.h`)
- **Legacy Keil** — µVision project uses **ARM Compiler 5 (ARMCC)**, not ARMClang
- Open: `KEIL/CardReader.uvprojx`

## Build (Keil MDK)

1. Install Keil MDK-ARM with **ARMCC V5** (legacy compiler pack)
2. Open `firmware/KEIL/CardReader.uvprojx`
3. If prompted for device pack, use generic **ARMCM4_FP** (or install GigaDevice GD32F4 pack for flash algo)
4. Project → Options → Target → confirm **ARMCC V5**
5. Build (`F7`) → flash via SWD (CMSIS-DAP / J-Link)

Output: `KEIL/Objects/CardReader.hex`

## Tree

```
firmware/
  CMSIS/gd32f407_regs.h     Register map (no vendor HAL)
  Startup/startup_gd32f407.s  ARMCC startup + vectors
  Inc/                      board.h bsp.h spi_bus.h usb_msc.h
  Src/                      system / bsp / spi / usb_msc / main
  Middlewares/mfrc522/      RC522 SPI driver
  Middlewares/ecc/          ECC API (demo signer; swap micro-ecc later)
  KEIL/CardReader.uvprojx   Legacy Keil project
  KEIL/CardReader.sct       Scatter file
```

## Verification

See **[VERIFY.md](VERIFY.md)** — register-map bugs fixed; USB BOT + real ECDSA still open.

## Features wired

| Feature | Status |
|---------|--------|
| 8 MHz HXTAL → 168 MHz PLL + FMC WS | OK (fixed) |
| LEDs PB1/PB2 | OK |
| Buzzer PB0 TIMER2 PWM | OK (base/enable fixed) |
| SPI0 + MFRC522 4-byte UID | OK |
| Virtual FAT MSC (UID.TXT, LOG.CSV, UID.SIG) | RAM image OK |
| USBFS device enumeration / BOT | Skeleton only — not host-mountable yet |
| ECC sign on UID | Demo MAC only — not ECDSA |

## Pin map

See `docs/pin-map.md` (SPI1/SPI0 on PA4–7, RC522 RST PC4, USB PA11/12).

## Flash / debug

- SWD: PA13/PA14
- Algorithm: use GD32F4xx flash algo from GigaDevice Keil pack when available

## Optional: real ECDSA P-256

Drop [micro-ecc](https://github.com/kmackay/micro-ecc) `.c/.h` into `Middlewares/ecc/` and replace the body of `ecc_sign` / `ecc_verify` — keep the same headers so `main.c` stays unchanged.
