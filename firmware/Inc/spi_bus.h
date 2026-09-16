#ifndef SPI_BUS_H
#define SPI_BUS_H

#include <stdint.h>

void spi0_init(void);
uint8_t spi0_xfer(uint8_t data);
void spi0_nss(uint8_t high);

#endif
