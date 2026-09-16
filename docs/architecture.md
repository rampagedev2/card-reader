# System Architecture

## Block diagram

```
                    ┌─────────────────────────────────────────┐
                    │              Enclosure (ABS)             │
                    │  ┌───────────────────────────────────┐  │
 USB-C 5V ──────────┼──┤ ESD │ LDO 3.3V │ Ferrite │ Cap    │  │
                    │  └───────────┬───────────────────────┘  │
                    │              │ 3V3 / GND                 │
                    │  ┌───────────▼───────────────────────┐  │
                    │  │         GD32F407VET6              │  │
                    │  │  USB FS │ SPI1 │ TIM │ GPIO       │  │
                    │  │  Custom MSC (internal Flash/RAM)  │  │
                    │  └───┬─────┴───┬──────────┬──────────┘  │
                    │      │         │          │             │
                    │      │    ┌────▼──┐  ┌────▼────┐        │
                    │      │    │MFRC522│  │ Buzzer  │        │
                    │      │    │+Ant. │  │ + LEDs  │        │
                    │      │    └───────┘  └─────────┘        │
                    │   Host PC                               │
                    │   (custom MSC)                          │
                    └─────────────────────────────────────────┘
```

## Subsystems

### 1. MCU core
- **GD32F407VET6**: 512 KB Flash, 192 KB SRAM, USB OTG FS device, hardware CRC/hash (CAU for AES/SHA; ECC in software).
- HSE: 8 MHz crystal → PLL → 168 MHz.

### 2. RFID (RC522)
- **MFRC522** QFN-32 + PCB loop antenna (~40×40 mm keep-out).
- SPI1 @ ≤10 MHz: SCK/MISO/MOSI/NSS + RST + IRQ.
- Read range target: 30–50 mm through ABS top (~1.5 mm).

### 3. USB Mass Storage (custom — no external flash)
- USB FS device on PA11 (DM) / PA12 (DP).
- **No W25Q128 / SPI NOR.** MSC is implemented in firmware:
  - **Option A:** Virtual FAT image in MCU Flash reserved pages (e.g. last 64–128 KB).
  - **Option B:** RAM disk rebuilt on each plug-in (volatile).
  - **Option C:** Fully custom MSC SCSI responses (host sees a drive; content generated on read).
- Host still mounts a removable volume; card UIDs / ECC signatures appear as files served by the stack.

### 4. Buzzer
- Passive piezo driven by N-MOSFET (AO3400) from TIM PWM (~2–4 kHz).

### 5. ECC
- Library: mbedTLS ECDSA P-256 or micro-ecc.
- Private key in MCU Flash with RDP.
- Flow: read UID → hash → ECDSA sign → expose via custom MSC as `UID.SIG`.

## Power tree

| Rail | Source | Load |
|------|--------|------|
| VBUS 5 V | USB-C | LDO in, buzzer |
| 3V3 | AP2112K-3.3 (600 mA) | MCU, MFRC522, LEDs |
| Peak | RFID TX burst ~26 mA + MCU ~50 mA | < 150 mA typical |

## Design choices for China production

| Choice | Why |
|--------|-----|
| On-board MFRC522 (not plug-in module) | Lower unit cost, better RF, single PCBA |
| No SPI NOR | Custom MSC; saves ~$1.85/unit + PCB area |
| 2-layer PCB | JLCPCB cheap; RF area with solid GND |
| USB-C only | Modern, still cheap at qty 500 |
| Soft-touch ABS | Looks premium without CNC metal |
| Stock blank enclosure | No mold NRE; buy shared-mold RFID shell |
