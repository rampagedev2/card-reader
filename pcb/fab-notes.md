# PCB Fabrication Notes

## JLCPCB order settings (recommended)

| Field | Setting |
|-------|---------|
| Base Material | FR-4 |
| Layers | 2 |
| Dimensions | 70 mm × 90 mm |
| Qty | 500 (or panel equivalent) |
| Thickness | 1.6 mm |
| Color | Green |
| Finish | HASL lead-free (or ENIG) |
| Copper Weight | 1 oz |
| Min via | 0.3 mm |
| Impedance | No (USB FS is tolerant) |
| Edge connector | No |
| Remove Order Number | Specify / Yes |
| Electrical Test | Yes |
| PCBA | Economic or Standard SMT |
| Parts | LCSC basic/extended (GD32 is Extended) |

## Assembly

- Side: Top only (buzzer may be TH — hand solder or select SMD piezo)
- Prefer full SMD BOM to avoid hand-solder fees
- AOI recommended for LQFP-100

## Test points (silkscreen)

| TP | Net |
|----|-----|
| TP1 | 3V3 |
| TP2 | GND |
| TP3 | VBUS |
| TP4 | RFID_IRQ |

## Coordinate file

Generate `.pos` from KiCad for pick-and-place. Origin: bottom-left board corner.
