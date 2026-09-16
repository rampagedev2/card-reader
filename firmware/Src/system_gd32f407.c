/**
 * @file system_gd32f407.c
 * @brief HXTAL 8 MHz → PLL 168 MHz — register level, no HAL
 */
#include "gd32f407_regs.h"

uint32_t SystemCoreClock = SYSTEM_CORE_CLOCK;

void SystemInit(void)
{
    /* FPU CP10/CP11 full access (CPACR), NOT SCB->CCR */
    CPACR |= (0xFU << 20);

    RCU->CTL |= RCU_CTL_HXTALEN;
    while ((RCU->CTL & RCU_CTL_HXTALSTB) == 0U) {
    }

    /* Flash wait states for 168 MHz (WS = 5 typical for 2.7–3.6 V) */
    FMC->WS = (FMC->WS & ~0xFU) | 5U;

    /* PLL: HXTAL/8 * 336 / 2 = 168 MHz; PLLQ=7 → 48 MHz for USBFS */
    RCU->PLL = RCU_PLL_PLLPSC(8) |
               RCU_PLL_PLLN(336) |
               RCU_PLL_PLLP(0) |
               RCU_PLL_PLLSEL |
               RCU_PLL_PLLQ(7);

    RCU->CTL |= RCU_CTL_PLLEN;
    while ((RCU->CTL & RCU_CTL_PLLSTB) == 0U) {
    }

    /* AHB=168, APB1=42 (div4), APB2=84 (div2) */
    RCU->CFG0 = (RCU->CFG0 & ~0xFCFCU) |
                RCU_CFG0_AHB_DIV1 | RCU_CFG0_APB1_DIV4 | RCU_CFG0_APB2_DIV2;
    RCU->CFG0 = (RCU->CFG0 & ~3U) | RCU_CFG0_SCS_PLL;
    while ((RCU->CFG0 & RCU_CFG0_SCSS_MASK) != RCU_CFG0_SCSS_PLL) {
    }

    SystemCoreClock = SYSTEM_CORE_CLOCK;
}
