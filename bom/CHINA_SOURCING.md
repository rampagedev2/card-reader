# China purchase checklist — 500 devices

All hardware from China. Ops (pack/test) excluded.

## Order 1 — LCSC (Shenzhen) — electronics

Cart these LCSC part numbers (qty ×500 unless noted):

| LCSC | Part | Qty/device |
|------|------|------------|
| C108421 | GD32F407VET6 | 1 |
| C51118 | AP2112K-3.3 | 1 |
| C2827693 | USBLC6-2SC6 | 1 |
| C20917 | AO3400 | 1 |
| C9002 | 8 MHz crystal | 1 |
| C96590 | Piezo buzzer | 1 |
| C165948 | USB-C 16P | 1 |
| C124378 | SWD 1x4 | 1 |
| C124411 | Header 1x8 | 1 |
| C2286 / C2287 | LED green / blue | 1 each |
| C2128 | 1N4148W | 1 |
| C107148 | Ferrite 0603 | 1 |
| C15850 | 10uF 0805 | 4 |
| C1525 | 100nF 0402 | 16 |
| C1555 | 22pF | 2 |
| C25905 | 5.1k | 2 |
| C11702 | 1k | 2 |
| C25744 | 10k | 2 |
| C25076 | 100R | 1 |
| C70098 | Assorted kit (optional) | 1 |

MCU verify: https://www.lcsc.com/product-detail/C108421.html (China stock).

## Order 2 — Alibaba — RC522 module ×500

https://www.alibaba.com/product-detail/Verified-Supplier-MFRC-522-RC-522_1601798247615.html  
3.3V SPI module with antenna.

## Order 3 — JLCPCB — bare PCB ×500

https://jlcpcb.com/ — 2-layer, ~105×60 mm, Gerbers from `pcb/`.

## Order 4 — SZOMK — AK-R-160 ×500 + CNC

https://www.chinaenclosure.com/products/SZOMK-Custom-IP54-abs-plastic-junction-box-RFID-enclosure-for-Card-reader-AK-R-160-118-75-22mm.html  
Alibaba: https://szokm.en.alibaba.com/ · ivy@szomk.com.cn  
CNC: card recess 86×54×0.8 + Type-C + 2× LED.

## Result

| Bucket | China? |
|--------|--------|
| MCU / ICs / passives | Yes — LCSC |
| RC522 module | Yes — Alibaba |
| Bare PCB | Yes — JLCPCB |
| Enclosure + CNC | Yes — SZOMK Shenzhen |

**Verdict: all purchasable from China.**
