/**
 * @file spi_bus.c — SPI0 master PA4-7 — register level
 */
#include "spi_bus.h"
#include "board.h"
#include "gd32f407_regs.h"

static void gpio_mode(GPIO_TypeDef *port, uint32_t pin, uint32_t mode,
                      uint32_t otype, uint32_t speed, uint32_t pupd, uint32_t af)
{
    uint32_t shift = pin * 2U;
    port->CTL = (port->CTL & ~(3U << shift)) | (mode << shift);
    if (otype)
        port->OMODE |= (1U << pin);
    else
        port->OMODE &= ~(1U << pin);
    port->OSPD = (port->OSPD & ~(3U << shift)) | (speed << shift);
    port->PUD = (port->PUD & ~(3U << shift)) | (pupd << shift);
    if (pin < 8U) {
        uint32_t s = pin * 4U;
        port->AFSEL0 = (port->AFSEL0 & ~(0xFU << s)) | (af << s);
    } else {
        uint32_t s = (pin - 8U) * 4U;
        port->AFSEL1 = (port->AFSEL1 & ~(0xFU << s)) | (af << s);
    }
}

void spi0_init(void)
{
    RCU->AHB1EN |= RCU_AHB1EN_PAEN | RCU_AHB1EN_PCEN;
    RCU->APB2EN |= RCU_APB2EN_SPI0EN;

    /* NSS software GPIO — mode OUTPUT */
    gpio_mode(RFID_NSS_PORT, RFID_NSS_PIN, GPIO_MODE_OUTPUT, 0, GPIO_OSPEED_50MHZ, 0, 0);
    gpio_mode(RFID_SCK_PORT, RFID_SCK_PIN, GPIO_MODE_AF, 0, GPIO_OSPEED_50MHZ, 0, 5U);
    gpio_mode(RFID_MISO_PORT, RFID_MISO_PIN, GPIO_MODE_AF, 0, GPIO_OSPEED_50MHZ, GPIO_PUPD_PULLUP, 5U);
    gpio_mode(RFID_MOSI_PORT, RFID_MOSI_PIN, GPIO_MODE_AF, 0, GPIO_OSPEED_50MHZ, 0, 5U);
    gpio_mode(RFID_RST_PORT, RFID_RST_PIN, GPIO_MODE_OUTPUT, 0, GPIO_OSPEED_50MHZ, 0, 0);
    gpio_mode(RFID_IRQ_PORT, RFID_IRQ_PIN, GPIO_MODE_INPUT, 0, 0, GPIO_PUPD_PULLUP, 0);

    spi0_nss(1);
    RFID_RST_PORT->BOP = (1U << RFID_RST_PIN);

    SPI0->CTL0 = 0;
    SPI0->CTL1 = 0;
    /* Master, soft NSS, MSB first, 8-bit, mode 0, BR = PCLK/16 */
    SPI0->CTL0 = SPI_CTL0_MSTMOD | SPI_CTL0_SWNSSEN | SPI_CTL0_SWNSS |
                 (3U << 3);
    SPI0->CTL0 |= SPI_CTL0_SPIEN;
}

void spi0_nss(uint8_t high)
{
    if (high)
        RFID_NSS_PORT->BOP = (1U << RFID_NSS_PIN);
    else
        RFID_NSS_PORT->BOP = (1U << (RFID_NSS_PIN + 16U));
}

uint8_t spi0_xfer(uint8_t data)
{
    while ((SPI0->STAT & SPI_STAT_TBE) == 0U) {
    }
    SPI0->DATA = data;
    while ((SPI0->STAT & SPI_STAT_RBNE) == 0U) {
    }
    return (uint8_t)SPI0->DATA;
}
