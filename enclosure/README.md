# Enclosure — Off-the-shelf (no mold, no logo)

Custom injection mold **removed**. Use a **stock / shared-mold (公模)** ABS card-reader shell bought blank from Shenzhen suppliers.

## Recommended product

| Field | Spec |
|-------|------|
| **Primary pick** | **Shiny Enclosure LK-AC05** |
| Outer size | **119 × 77 × 22 mm** |
| Material | ABS, black (or white) |
| Logo | **None** (order blank / no silkscreen) |
| Fit | Fits ~70×90 mm PCB with margin; thin lid OK for 13.56 MHz |
| MOQ | 2 pcs (stock) |
| Lead time | ~3–5 working days after payment |
| Supplier | [Shiny Enclosure LK-AC05](https://www.shinyenclosure.com/lk-ac05-119-77-22mm-shiny-enclosure-door-access-control-box-ic-card-reader-electronic-enclosure-for-security-system_p581.html) |
| Contact | bonnie@shinyenclosure.com / WhatsApp +86 13682453603 |

Ask for: **blank shell, no logo, black ABS, with screws, PDF/CAD drawing, optional USB-C cutout**.

## Alternatives (same market)

| Model | Size (mm) | Source | Notes |
|-------|-----------|--------|-------|
| **LK-AC03** | 115 × 77 × 20 | [Shiny](https://www.shinyenclosure.com/lk-ac03-hot-sales-plastic-electrical-enclosure-boxes-door-access-control-system-rfid-reader-enclosure-115x77x20mm_p1107.html) | Slightly thinner; good RFID form |
| **LK-AC01** | 119 × 54 × 23 | Shiny | Narrower — may need PCB shrink to ~50 mm width |
| **HF-K-208** | 123 × 99 × 26 | [Hongfa Shunda](http://m.hfsdkt.com/menjindukawaike/34-2250.html) | Larger; easier PCB fit |
| Generic DIY box | 100 × 60 × 25 | AliExpress (~$1.5–2.5) | Cheapest; less “reader-like” look |

Hongfa / 1688 “门禁读卡器外壳” listings often quote about **¥10/set (~$1.40) at 500–999**, **¥15 (~$2.10) at 100–499**, blank ABS, no logo unless you pay for print.

## Price used in BOM (@500)

| Item | USD |
|------|-----|
| Blank ABS shell (LK-AC05 class) | **$1.40** |
| USB-C + LED hole machining (optional CNC/drill) | **$0.25** |
| Screws (if not included) | **$0.10** |
| **Enclosure total** | **~$1.75** |
| ~~Custom mold~~ | **$0** |

## Fit notes for our PCB

1. Resize PCB to **~65 × 85 mm** (or confirm internal boss spacing from supplier CAD) before Gerbers.  
2. Place USB-C on the end that matches the stock cutout — or pay for one USB-C opening.  
3. Keep antenna under the flat lid area; avoid metal stickers.  
4. No brand logo on case (per your request).

## What changed vs previous “Slate” custom case

| | Custom mold | Stock shell |
|--|-------------|-------------|
| NRE | ~$2,500 | **$0** |
| Unit shell | ~$1.50 + $5 amort. | **~$1.75 all-in** |
| Lead time | 4–6 weeks tooling | **Days** |
| Look | Unique | Standard access-control style (still clean blank) |

OpenSCAD `card_reader_case.scad` is kept only as a mechanical reference; **do not tool it**.
