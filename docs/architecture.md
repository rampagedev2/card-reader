# System Architecture

**UX:** User **places the card on top** of the device (recessed lid). RC522 under the lid reads it.

## Block diagram

```
              [ CARD on top ]
                    |
 USB-C 5V -> ESD -> LDO 3.3V -+- GD32F407VET6
                              +- RC522 MODULE (under lid, antenna up)
                              +- Buzzer / LEDs
                              +- Custom USB MSC (MCU Flash/RAM)
```

## Subsystems

### MCU
GD32F407VET6, 168 MHz, USB FS device, custom MSC + software ECC.

### RFID — RC522 module (top-read)
Ready **RC522** board under the lid. Card is placed **on the top surface**, not inserted in a slot.
Wired to SPI1 via header **J3**. Module antenna faces the lid.

### USB MSC
Custom firmware; no SPI NOR.

### Buzzer / LEDs
PWM piezo + status LEDs (feedback when card is read).

### Enclosure
**SZOMK AK-R-160** (118×75×22 mm): CNC top card recess + Type-C + LEDs. China, no battery.

## Power

| Rail | Load |
|------|------|
| 5V USB | LDO in, buzzer |
| 3V3 | MCU, **RC522 module**, LEDs |
