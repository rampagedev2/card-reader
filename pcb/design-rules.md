# PCB Design Rules — Card Reader Rev A

## Board

| Parameter | Value |
|-----------|-------|
| Size | **70 × 90 mm** |
| Layers | **2** (Top signal+RF, Bottom GND+signal) |
| Thickness | 1.6 mm FR-4 |
| Copper | 1 oz (35 µm) |
| Finish | HASL lead-free (ENIG optional +$ for LQFP fine pitch) |
| Min trace / space | 0.15 / 0.15 mm (6 / 6 mil) |
| Min via | 0.3 mm drill / 0.55 mm pad |
| Mask | Green, silkscreen white |
| Fab | JLCPCB / PCBWay China |

**Recommendation:** ENIG if LQFP-100 yield concerns; HASL is OK for qty 500 with good stencil.

## Stackup

```
TOP:    Components, RF antenna, SPI, USB short runs
DIELEC: 1.5 mm FR-4 core approx
BOTTOM: Solid GND pour, few jumpers, SWD pads
```

## Floorplan (see `pcb_layout.svg`)

```
Y=90 ┌──────────────────────────────────────┐
     │  [USB-C]    LDO    ESD               │  short edge = cable side
     │           [GD32F407 LQFP100]         │
     │  Flash                               │
     │  Buzzer  LEDs                        │
     │ ───────────────────────────────────  │  RF keep-out boundary
     │                                      │
     │         ANTENNA 40×40                │  under lid RF window
     │         MFRC522 nearby               │
Y=0  └──────────────────────────────────────┘
   X=0                                   X=70
```

## Critical constraints

1. **Antenna keep-out**: no copper, no components, no screws in 45×45 mm zone except antenna traces & matching.
2. **USB DP/DM**: length match ±2 mm; run over continuous GND; ESD within 5 mm of connector.
3. **Crystal**: within 8 mm of OSC pins; guard GND ring.
4. **Decoupling**: 100 nF under/near each VDD pair; via to GND plane immediately.
5. **Thermal**: EP pad of MFRC522 via-stitched to GND.
6. **Mounting**: 4× M2.5 holes at corners, 3.2 mm ID, keep 5 mm copper clearance from antenna zone.

## Panelization (qty 500)

- Panel 2×3 or 2×4 with V-cut or mouse bites
- Fiducials for SMT
- Tooling strips 5–8 mm

## Gerber outputs expected

`GTL GBL GTS GBS GTO GBO GKO TXT(drill) CPL(pos) BOM`

Generate from KiCad after redrawing from SVG sheets + netlist.
