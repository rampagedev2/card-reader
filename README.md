# Card Reader — GD32F407VET6 + RC522

Desktop USB card reader: user **places the card on top**; RFID (RC522 module), buzzer, USB Mass Storage, ECC.

| Item | Spec |
|------|------|
| MCU | GigaDevice **GD32F407VET6** (Cortex-M4 @ 168 MHz, LQFP-100) |
| RFID | **RC522 ready module** (SPI via header J3) |
| Storage | **Custom USB MSC** (MCU internal Flash / virtual disk — no SPI NOR) |
| USB | USB-C (device FS), customized Mass Storage Class |
| Audio | Passive piezo buzzer |
| Crypto | Software ECC (secp256r1) on Cortex-M4 FPU |
| Power | USB 5 V → 3.3 V LDO |
| PCB | 70 × 90 mm, 2-layer FR-4 |
| Enclosure | **SZOMK AK-R-55** (154×110×35) — list $1.50; CNC card + LED + Type-C |

## Features

1. **Read Card** — MIFARE Classic / Ultralight / ISO14443A via SPI to MFRC522  
2. **Buzzer** — PWM-driven piezo for tap / OK / error tones  
3. **USB Mass Storage** — appears as a removable drive; card UIDs / logs written as files  
4. **ECC calculation** — sign / verify card payloads (mbedTLS / micro-ecc)

## Folder map

```
bom/           Bill of materials + pricing (qty 500, China)
docs/          Architecture, pin map, production notes
schematic/     Multi-sheet schematic (SVG + netlist)
pcb/           PCB layout, stackup, design rules
enclosure/     Mechanical design (OpenSCAD + drawings)
firmware/      Feature map / suggested stack
```

## Cost snapshot (500 units, China)

See the interactive cost canvas and `bom/BOM_500pcs.csv`.

| Category | Per unit | 500 batch |
|----------|----------|-----------|
| Electronics (parts + bare PCB) | ~$6.60 | ~$3,300 |
| AK-R-55 + CNC (est @500) | ~$1.80 | ~$900 |
| **Total (hand build hardware)** | **~$8.40** | **~$4,200** |

Buy: https://szomkbox.en.made-in-china.com/product/pvYQDhkWTxAn/China-Szomk-Card-Reader-Housing-for-Electronics-RFID-Project-Box.html — Ops excluded.

## Quick start (hardware)

1. Review `docs/architecture.md` and `schematic/01_system.svg`  
2. Import netlist / redraw in KiCad from `schematic/` sheets  
3. Fabricate PCB per `pcb/design-rules.md` (JLCPCB recommended)  
4. Print enclosure prototype from `enclosure/card_reader_case.scad`  
5. Flash firmware with SWD (PA13/PA14)
