#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include "gd32f407_regs.h"

void SystemInit(void);
void board_init(void);
void delay_ms(uint32_t ms);
uint32_t millis(void);

void led_status(uint8_t on);
void led_rf(uint8_t on);
void buzzer_beep(uint16_t freq_hz, uint16_t ms);
void buzzer_ok(void);
void buzzer_err(void);

#endif
