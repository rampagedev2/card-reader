# Firmware Feature Map

Not a full firmware tree — recommended stack for GD32F407VET6.

## Suggested stack

| Layer | Choice |
|-------|--------|
| IDE | Keil MDK / GD32 Eclipse / PlatformIO |
| SPL/HAL | GD32F4xx Firmware Library |
| USB | Custom MSC (or TinyUSB MSC with custom storage callbacks) |
| Storage | **No SPI NOR** — MCU Flash sector / RAM / virtual SCSI |
| RFID | miguelbalboa/rfid port or NXP MFRC522 driver |
| Crypto | mbedTLS ECDSA P-256 |
| RTOS | Optional FreeRTOS (USB + RFID tasks) |

## Custom USB MSC (no W25Q128)

Implement MSC `READ(10)` / `WRITE(10)` (if needed) against:

1. A small FAT12/16 image baked into Flash, **or**
2. On-the-fly directory/file contents built when the host reads sectors

Typical exposed files: `UID.TXT`, `LOG.CSV`, `UID.SIG`.

## Behaviors

1. Enumerate as MSC `CARDREADER`  
2. Poll IRQ / 50 ms SPI poll for cards  
3. On UID: beep pattern A; update MSC-visible files; sign ECC  
4. Error: beep pattern B (two short)  

## Factory

- Flash bootloader + app via SWD  
- Provision ECC private key per device (or shared product key)  
- No NOR format step  
