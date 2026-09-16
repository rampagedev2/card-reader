#ifndef USB_MSC_H
#define USB_MSC_H

#include <stdint.h>

void usb_msc_init(void);
void usb_msc_poll(void);
/* Update virtual files when a card UID is read (ASCII hex) */
void usb_msc_set_uid(const uint8_t *uid, uint8_t len);
void usb_msc_append_log(const char *line);
void usb_msc_set_signature(const uint8_t *sig, uint8_t len);

#endif
