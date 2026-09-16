# Firmware verification

Audit date: 2026-09-15. Against GD32F4xx CMSIS / datasheet (RCU AHB1EN @ 0x30, TIMER2 @ 0x40000400, USBFS AHB2EN bit7).

## Verdict

**Clock / GPIO / SPI / RC522 / TIMER2 / SysTick / vector table: corrected and structurally sound.**  
**USB MSC host mount and real ECDSA: not production-ready** (stubs / demo MAC).

## Bugs found and fixed

| Issue | Impact | Fix |
|-------|--------|-----|
| RCU struct used wrong offsets (`AHBEN` like F1) | Clocks never enabled | `AHB1EN`/`AHB2EN`/`APB1EN`/`APB2EN` layout |
| USBFS clock on wrong enable bit | USBFS dead | `RCU_AHB2EN` bit 7 |
| TIMER2 base / enable wrong | Buzzer silent or wrong timer | Base `0x40000400`, `APB1EN` bit 1 |
| FPU via `SCB->CCR` | Illegal; faults with FP ABI | `CPACR` CP10/CP11 |
| No FMC wait states @ 168 MHz | Unstable Flash fetch | `FMC->WS = 5` |
| IRQ vectors 0..66 = 0 | Spurious IRQ → HardFault | `Default_Handler` |
| `hash_uid` `% uid->size` if size 0 | Div-by-zero | Guard `n = size ? size : 1` |

## Still incomplete (by design / next work)

1. **USBFS MSC** — clock, soft-connect, IRQ shell only. No EP0 SETUP, no BOT (CBW/CSW), so host will **not** mount the FAT disk yet. RAM FAT builder itself is OK.
2. **ECC** — `ecc_sign` is a keyed XOR demo, **not** ECDSA P-256. Swap in micro-ecc (or similar) behind the same API.
3. **RC522** — REQA + anticoll cascade level 1 only (4-byte UID). No cascade 2/3 (7/10-byte UIDs), no HALT A.
4. **Hardware bring-up** — not run on silicon in this audit; needs Keil build + SWD check of VERSION (`0x91`/`0x92`) and USB enumerate.

## What should work after flash (expected)

- 8 MHz HXTAL → PLL 168 MHz, APB1 42 / timers 84, PLLQ → 48 MHz USB clock source
- LEDs PB1/PB2, buzzer PWM on PB0 TIMER2_CH2
- SPI0 @ PA4–7 ↔ RC522; UID read for classic 4-byte cards
- On card: update in-RAM `UID.TXT` / `LOG.CSV` / `UID.SIG` (visible once USB BOT is finished)
