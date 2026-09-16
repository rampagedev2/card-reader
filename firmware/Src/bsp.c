/**
 * @file bsp.c — GPIO / SysTick / buzzer TIMER2 — no HAL
 */
#include "bsp.h"
#include "board.h"

static volatile uint32_t g_ms;

static void gpio_clock_enable(void)
{
    RCU->AHB1EN |= RCU_AHB1EN_PAEN | RCU_AHB1EN_PBEN | RCU_AHB1EN_PCEN;
}

static void gpio_mode(GPIO_TypeDef *port, uint32_t pin, uint32_t mode,
                      uint32_t otype, uint32_t speed, uint32_t pupd, uint32_t af)
{
    uint32_t shift = pin * 2U;
    port->CTL = (port->CTL & ~(3U << shift)) | (mode << shift);
    if (mode == GPIO_MODE_OUTPUT || mode == GPIO_MODE_AF) {
        if (otype)
            port->OMODE |= (1U << pin);
        else
            port->OMODE &= ~(1U << pin);
        port->OSPD = (port->OSPD & ~(3U << shift)) | (speed << shift);
    }
    port->PUD = (port->PUD & ~(3U << shift)) | (pupd << shift);
    if (pin < 8U) {
        uint32_t s = pin * 4U;
        port->AFSEL0 = (port->AFSEL0 & ~(0xFU << s)) | (af << s);
    } else {
        uint32_t s = (pin - 8U) * 4U;
        port->AFSEL1 = (port->AFSEL1 & ~(0xFU << s)) | (af << s);
    }
}

static void gpio_write(GPIO_TypeDef *port, uint32_t pin, uint8_t high)
{
    if (high)
        port->BOP = (1U << pin);
    else
        port->BOP = (1U << (pin + 16U));
}

void SysTick_Handler(void)
{
    g_ms++;
}

void delay_ms(uint32_t ms)
{
    uint32_t t = g_ms;
    while ((g_ms - t) < ms) {
    }
}

uint32_t millis(void)
{
    return g_ms;
}

static void systick_init(void)
{
    SysTick->LOAD = (SYSTEM_CORE_CLOCK / 1000U) - 1U;
    SysTick->VAL = 0;
    SysTick->CTRL = 5U; /* CLKSOURCE=CPU, ENABLE; TICKINT set below */
    SysTick->CTRL = 7U; /* +TICKINT */
}

static void buzzer_tim_init(void)
{
    RCU->APB1EN |= RCU_APB1EN_TIMER2EN;
    /* PB0 AF2 = TIMER2_CH2 */
    gpio_mode(BUZZER_PORT, BUZZER_PIN, GPIO_MODE_AF, GPIO_OTYPE_PP,
              GPIO_OSPEED_50MHZ, GPIO_PUPD_NONE, 2U);

    TIMER2->CTL0 = 0;
    /* APB1 timer clock ~84 MHz when APB1=/4 → PSC for ~1 MHz */
    TIMER2->PSC = 83U;
    TIMER2->CAR = 1000U;
    /* CH2 PWM mode 1 on TIMER2 (PB0 = TIMER2_CH2) */
    TIMER2->CHCTL1 = (6U << 4);
    TIMER2->CHCTL2 |= (1U << 8); /* CH2E */
    TIMER2->CH2CV = 0;
    TIMER2->CTL0 |= (1U << 0);
}

void board_init(void)
{
    gpio_clock_enable();
    systick_init();

    gpio_mode(LED_STATUS_PORT, LED_STATUS_PIN, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP,
              GPIO_OSPEED_50MHZ, GPIO_PUPD_NONE, 0);
    gpio_mode(LED_RF_PORT, LED_RF_PIN, GPIO_MODE_OUTPUT, GPIO_OTYPE_PP,
              GPIO_OSPEED_50MHZ, GPIO_PUPD_NONE, 0);
    led_status(0);
    led_rf(0);

    buzzer_tim_init();
}

void led_status(uint8_t on)
{
    gpio_write(LED_STATUS_PORT, LED_STATUS_PIN, on);
}

void led_rf(uint8_t on)
{
    gpio_write(LED_RF_PORT, LED_RF_PIN, on);
}

void buzzer_beep(uint16_t freq_hz, uint16_t ms)
{
    if (freq_hz < 100U)
        freq_hz = 100U;
    TIMER2->CAR = (1000000U / freq_hz) - 1U;
    TIMER2->CH2CV = (TIMER2->CAR + 1U) / 2U;
    delay_ms(ms);
    TIMER2->CH2CV = 0;
}

void buzzer_ok(void)
{
    buzzer_beep(2000, 80);
}

void buzzer_err(void)
{
    buzzer_beep(800, 60);
    delay_ms(40);
    buzzer_beep(800, 60);
}
