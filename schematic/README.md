# Schematics Index

Open SVG files in a browser, VS Code, or Inkscape.

| Sheet | File | Content |
|-------|------|---------|
| 01 | `01_system.svg` | Block diagram / system overview |
| 02 | `02_power.svg` | USB-C, ESD, ferrite, LDO 3.3 V |
| 03 | `03_mcu.svg` | GD32F407VET6 pin connections |
| 04 | `04_rfid.svg` | RC522 **module** header J3 wiring |
| 05 | `05_usb_flash_buzzer.svg` | Custom USB MSC, buzzer, LEDs, ECC notes |

Supporting: `netlist.txt`

## Path to Gerbers

1. Create KiCad 8 project  
2. Redraw sheets using these SVGs + `docs/pin-map.md`  
3. Assign footprints (LQFP-100, QFN-32, SOIC-8, …)  
4. Import PCB floorplan from `../pcb/pcb_layout.svg`  
5. Run DRC per `../pcb/design-rules.md`  
6. Plot Gerbers for JLCPCB  

These SVGs are **design-complete electrically** for quoting and review; KiCad redraw is the manufacturing gate.
