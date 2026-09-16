/**
 * @file gd32f407_regs.h
 * @brief Minimal GD32F407 register map — bare-metal, no HAL/SPL
 *        Layout matches GigaDevice GD32F4xx CMSIS (AHB1EN @ 0x30, etc.)
 */
#ifndef GD32F407_REGS_H
#define GD32F407_REGS_H

#include <stdint.h>

#define __I  volatile const
#define __O  volatile
#define __IO volatile

#define PERIPH_BASE     0x40000000UL
#define APB1_BASE       (PERIPH_BASE + 0x00000000UL)
#define APB2_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1_BASE       (PERIPH_BASE + 0x00020000UL)

/* TIMER1 @ 0x40000000, TIMER2 @ 0x40000400 (datasheet) */
#define TIMER1_BASE     (APB1_BASE + 0x0000UL)
#define TIMER2_BASE     (APB1_BASE + 0x0400UL)
#define RCU_BASE        (AHB1_BASE + 0x3800UL)
#define FMC_BASE        (AHB1_BASE + 0x3C00UL)
#define GPIOA_BASE      (AHB1_BASE + 0x0000UL)
#define GPIOB_BASE      (AHB1_BASE + 0x0400UL)
#define GPIOC_BASE      (AHB1_BASE + 0x0800UL)
#define SPI0_BASE       (APB2_BASE + 0x3000UL)
#define USBFS_BASE      0x50000000UL
#define SYSTICK_BASE    0xE000E010UL
#define SCB_BASE        0xE000ED00UL
#define CPACR_ADDR      0xE000ED88UL
#define NVIC_ISER_BASE  0xE000E100UL

/* RCU — GD32F4xx offsets (Zephyr / Gigadevice CMSIS) */
typedef struct {
    __IO uint32_t CTL;       /* 0x00 */
    __IO uint32_t PLL;       /* 0x04 PLLCFG */
    __IO uint32_t CFG0;      /* 0x08 */
    __IO uint32_t INT;       /* 0x0C */
    __IO uint32_t AHB1RST;   /* 0x10 */
    __IO uint32_t AHB2RST;   /* 0x14 */
    __IO uint32_t AHB3RST;   /* 0x18 */
    uint32_t RESERVED0;      /* 0x1C */
    __IO uint32_t APB1RST;   /* 0x20 */
    __IO uint32_t APB2RST;   /* 0x24 */
    uint32_t RESERVED1[2];   /* 0x28 */
    __IO uint32_t AHB1EN;    /* 0x30 */
    __IO uint32_t AHB2EN;    /* 0x34 */
    __IO uint32_t AHB3EN;    /* 0x38 */
    uint32_t RESERVED2;      /* 0x3C */
    __IO uint32_t APB1EN;    /* 0x40 */
    __IO uint32_t APB2EN;    /* 0x44 */
    uint32_t RESERVED3[2];
    __IO uint32_t AHB1SPEN;
    __IO uint32_t AHB2SPEN;
    __IO uint32_t AHB3SPEN;
    uint32_t RESERVED4;
    __IO uint32_t APB1SPEN;
    __IO uint32_t APB2SPEN;
    uint32_t RESERVED5[2];
    __IO uint32_t BDCTL;
    __IO uint32_t RSTSCK;
    uint32_t RESERVED6[2];
    __IO uint32_t PLLI2S;
    __IO uint32_t PLLSAI;
    __IO uint32_t CFG1;
    uint32_t RESERVED7;
    __IO uint32_t ADDCTL;
    uint32_t RESERVED8[2];
    __IO uint32_t ADDINT;
    uint32_t RESERVED9[4];
    __IO uint32_t ADDAPB1RST;
    __IO uint32_t ADDAPB1EN;
    __IO uint32_t ADDAPB1SPEN;
} RCU_TypeDef;

typedef struct {
    __IO uint32_t WS;        /* 0x00 wait state */
    __IO uint32_t KEY;
    __IO uint32_t OBKEY;
    __IO uint32_t STAT;
    __IO uint32_t CTL;
    __IO uint32_t ADDR;
    uint32_t RESERVED0;
    __IO uint32_t OBSTAT;
    __IO uint32_t WP;
} FMC_TypeDef;

typedef struct {
    __IO uint32_t CTL;
    __IO uint32_t OMODE;
    __IO uint32_t OSPD;
    __IO uint32_t PUD;
    __IO uint32_t ISTAT;
    __IO uint32_t OCTL;
    __IO uint32_t BOP;
    __IO uint32_t LOCK;
    __IO uint32_t AFSEL0;
    __IO uint32_t AFSEL1;
} GPIO_TypeDef;

typedef struct {
    __IO uint32_t CTL0;
    __IO uint32_t CTL1;
    __IO uint32_t STAT;
    __IO uint32_t DATA;
    __IO uint32_t CRCPOLY;
    __IO uint32_t RCRC;
    __IO uint32_t TCRC;
    __IO uint32_t I2SCTL;
    __IO uint32_t I2SPSC;
    __IO uint32_t QCTL;
} SPI_TypeDef;

typedef struct {
    __IO uint32_t CTL0;
    __IO uint32_t CTL1;
    __IO uint32_t SMCFG;
    __IO uint32_t DMAINTEN;
    __IO uint32_t INTF;
    __IO uint32_t SWEVG;
    __IO uint32_t CHCTL0;
    __IO uint32_t CHCTL1;
    __IO uint32_t CHCTL2;
    __IO uint32_t CNT;
    __IO uint32_t PSC;
    __IO uint32_t CAR;
    __IO uint32_t CREP;
    __IO uint32_t CH0CV;
    __IO uint32_t CH1CV;
    __IO uint32_t CH2CV;
    __IO uint32_t CH3CV;
    __IO uint32_t CCHP;
    __IO uint32_t DMACFG;
    __IO uint32_t DMATB;
} TIMER_TypeDef;

typedef struct {
    __IO uint32_t CTRL;
    __IO uint32_t LOAD;
    __IO uint32_t VAL;
    __I  uint32_t CALIB;
} SysTick_TypeDef;

typedef struct {
    __IO uint32_t CPUID;
    __IO uint32_t ICSR;
    __IO uint32_t VTOR;
    __IO uint32_t AIRCR;
    __IO uint32_t SCR;
    __IO uint32_t CCR;
    __IO uint8_t  SHP[12];
    __IO uint32_t SHCSR;
} SCB_TypeDef;

#define RCU     ((RCU_TypeDef *)RCU_BASE)
#define FMC     ((FMC_TypeDef *)FMC_BASE)
#define GPIOA   ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC   ((GPIO_TypeDef *)GPIOC_BASE)
#define SPI0    ((SPI_TypeDef *)SPI0_BASE)
#define TIMER2  ((TIMER_TypeDef *)TIMER2_BASE)
#define SysTick ((SysTick_TypeDef *)SYSTICK_BASE)
#define SCB     ((SCB_TypeDef *)SCB_BASE)
#define CPACR   (*(__IO uint32_t *)CPACR_ADDR)

/* RCU CTL */
#define RCU_CTL_IRC8MEN     (1U << 0)
#define RCU_CTL_HXTALEN     (1U << 16)
#define RCU_CTL_HXTALSTB    (1U << 17)
#define RCU_CTL_PLLEN       (1U << 24)
#define RCU_CTL_PLLSTB      (1U << 25)

/* RCU CFG0 */
#define RCU_CFG0_SCS_PLL    (2U << 0)
#define RCU_CFG0_SCSS_MASK  (3U << 2)
#define RCU_CFG0_SCSS_PLL   (2U << 2)
#define RCU_CFG0_AHB_DIV1   (0U << 4)
#define RCU_CFG0_APB1_DIV4  (5U << 10)
#define RCU_CFG0_APB2_DIV2  (4U << 13)

/* RCU PLL: 8/8*336/2 = 168 MHz, Q=7 → 48 MHz USB */
#define RCU_PLL_PLLPSC(x)   ((uint32_t)((x) & 0x3FU))
#define RCU_PLL_PLLN(x)     ((uint32_t)((x) & 0x1FFU) << 6)
#define RCU_PLL_PLLP(x)     ((uint32_t)((x) & 3U) << 16)
#define RCU_PLL_PLLSEL      (1U << 22)
#define RCU_PLL_PLLQ(x)     ((uint32_t)((x) & 0xFU) << 24)

/* Clocks */
#define RCU_AHB1EN_PAEN     (1U << 0)
#define RCU_AHB1EN_PBEN     (1U << 1)
#define RCU_AHB1EN_PCEN     (1U << 2)
#define RCU_AHB2EN_USBFSEN  (1U << 7)
#define RCU_APB2EN_SPI0EN   (1U << 12)
#define RCU_APB1EN_TIMER2EN (1U << 1)  /* TIMER2 = bit1 (TIMER1=bit0) */

/* GPIO */
#define GPIO_MODE_INPUT     0U
#define GPIO_MODE_OUTPUT    1U
#define GPIO_MODE_AF        2U
#define GPIO_MODE_ANALOG    3U
#define GPIO_OTYPE_PP        0U
#define GPIO_OTYPE_OD        1U
#define GPIO_OSPEED_50MHZ    2U
#define GPIO_PUPD_NONE       0U
#define GPIO_PUPD_PULLUP     1U
#define GPIO_PUPD_PULLDOWN   2U

/* SPI0 */
#define SPI_CTL0_SPIEN      (1U << 6)
#define SPI_CTL0_MSTMOD     (1U << 2)
#define SPI_CTL0_SWNSS      (1U << 8)
#define SPI_CTL0_SWNSSEN    (1U << 9)
#define SPI_STAT_TBE        (1U << 1)
#define SPI_STAT_RBNE       (1U << 0)

/* USBFS IRQ — same index as STM32F4 OTG_FS on GD32F407 */
#define USBFS_IRQn          67

static inline void nvic_enable_irq(uint32_t irq)
{
    ((__IO uint32_t *)NVIC_ISER_BASE)[irq >> 5] = (1UL << (irq & 0x1FU));
}

#define SYSTEM_CORE_CLOCK   168000000UL

#endif /* GD32F407_REGS_H */
