# Where to buy (manual manufacture + RC522 module)

Hand-build: bare PCB from JLCPCB, parts from LCSC, **RC522 module** from Alibaba, **SZOMK AK-R-160** shell.

## China sourcing verified

Every line is buyable from **China** (no DigiKey/RS/OKW/Hammond required).

| Source | Location | What |
|--------|----------|------|
| [LCSC](https://www.lcsc.com/) | Shenzhen | MCU, LDO, ESD, passives, connectors, LEDs, buzzer, crystal |
| [JLCPCB](https://jlcpcb.com/) | Shenzhen | Bare 2-layer PCB |
| [Alibaba RC522](https://www.alibaba.com/product-detail/Verified-Supplier-MFRC-522-RC-522_1601798247615.html) | China sellers | RC522 RFID module |
| [SZOMK](https://www.chinaenclosure.com/products/SZOMK-Custom-IP54-abs-plastic-junction-box-RFID-enclosure-for-Card-reader-AK-R-160-118-75-22mm.html) | Shenzhen | AK-R-160 shell + CNC |

| Ref | Part | China buy | Origin note |
|-----|------|-----------|-------------|
| U1 | GD32F407VET6 | LCSC [C108421](https://www.lcsc.com/product-detail/C108421.html) | GigaDevice **Beijing** — in stock ~15k on LCSC |
| MOD1 | RC522 module | Alibaba | China OEM modules |
| U4 | AP2112K-3.3 | LCSC C51118 | Stocked on LCSC |
| U5 | USBLC6-2SC6 | LCSC C2827693 | ST or China-compat via LCSC |
| Q1 | AO3400 | LCSC C20917 | Common China SOT-23 FET |
| All passives / headers / USB-C / LEDs / buzzer / crystal | LCSC | All C-numbers below |
| PCB1 | Bare PCB | JLCPCB | China fab |
| ENC1 | AK-R-160 | SZOMK | Shenzhen factory |
| ENC_CNC | Recess + Type-C + LED | SZOMK | Same order |

**Not required:** DigiKey, Mouser, RS, OKW, Hammond, or any non-China enclosure maker.

## RFID (module — not discrete MFRC522 chip)

| Ref | Part | Buy |
|-----|------|-----|
| MOD1 | RC522 RFID module (SPI + antenna) | https://www.alibaba.com/product-detail/Verified-Supplier-MFRC-522-RC-522_1601798247615.html |
| J3 | 1x8 header for module | https://www.lcsc.com/product-detail/C124411.html |

Module pins (typical): **3.3V, RST, GND, IRQ, MISO, MOSI, SCK, SDA(NSS)** — 3.3V only (not 5V).

## Main ICs

| Ref | Part | Buy |
|-----|------|-----|
| U1 | GD32F407VET6 | https://www.lcsc.com/product-detail/C108421.html |
| U4 | AP2112K-3.3 | https://www.lcsc.com/product-detail/C51118.html |
| U5 | USB ESD USBLC6-2 | https://www.lcsc.com/product-detail/C2827693.html |
| Q1 | AO3400 | https://www.lcsc.com/product-detail/C20917.html |

## Connectors / audio / clock / LEDs

| Ref | Part | Buy |
|-----|------|-----|
| J1 | USB-C | https://www.lcsc.com/product-detail/C165948.html |
| J2 | SWD header | https://www.lcsc.com/product-detail/C124378.html |
| BZ1 | Piezo buzzer | https://www.lcsc.com/product-detail/C96590.html |
| X1 | 8 MHz crystal | https://www.lcsc.com/product-detail/C9002.html |
| LED1 | Green 0603 | https://www.lcsc.com/product-detail/C2286.html |
| LED2 | Blue 0603 | https://www.lcsc.com/product-detail/C2287.html |
| D1 | 1N4148W | https://www.lcsc.com/product-detail/C2128.html |
| L1 | Ferrite bead | https://www.lcsc.com/product-detail/C107148.html |

## Passives

| Ref | Part | Buy |
|-----|------|-----|
| C_BULK | 10uF 0805 | https://www.lcsc.com/product-detail/C15850.html |
| C_DEC | 100nF 0402 | https://www.lcsc.com/product-detail/C1525.html |
| C_XTAL | 22pF NP0 | https://www.lcsc.com/product-detail/C1555.html |
| R_CC | 5.1k | https://www.lcsc.com/product-detail/C25905.html |
| R_LED | 1k | https://www.lcsc.com/product-detail/C11702.html |
| R_BOOT / R_RST | 10k | https://www.lcsc.com/product-detail/C25744.html |
| R_BUZ | 100R | https://www.lcsc.com/product-detail/C25076.html |
| Kit | Assorted 0402 | https://www.lcsc.com/product-detail/C70098.html |

## PCB and enclosure

| Item | Buy |
|------|-----|
| Bare PCB | https://jlcpcb.com/ |
| **Shell SZOMK AK-R-160 (selected)** | https://www.chinaenclosure.com/products/SZOMK-Custom-IP54-abs-plastic-junction-box-RFID-enclosure-for-Card-reader-AK-R-160-118-75-22mm.html |
| Same model (alt page) | https://www.chinaenclosure.com/products/Shenzhen-new-product-abs-plastic-access-control-card-reader-118X75X22mm-enclosure-supply-AK-R-160.html |
| SZOMK Alibaba | https://szokm.en.alibaba.com/ |

**118×75×22 mm**, China, no battery. CNC: card recess + Type-C + 2× LED. ivy@szomk.com.cn

## Cost (hardware only)

| | Buy 1 | Buy 500 (per device) | 500 batch |
|--|-------|----------------------|-----------|
| Parts + bare PCB | ~$8.36 | ~$6.60 | ~$3,300 |
| AK-R-160 + CNC | ~$6.00 | ~$1.70 | ~$850 |
| **Total** | **~$14.36** | **~$8.30** | **~$4,150** |

Buy-1 uses LCSC/Alibaba sample or MOQ prices (see `Unit_USD_1` / `Ext_USD_1` in `BOM_500pcs.csv`).
