#include <cstdint>

#include "stm32f0xx.h"

static void SystemClock_Config(void);

int main()
{
    uint32_t i = 0U;

    // Configure system clock (48 MHz)
    SystemClock_Config();

    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Configure PA5 as output
    GPIOA->MODER &= ~GPIO_MODER_MODER5_Msk;
    GPIOA->MODER |= (0x01U << GPIO_MODER_MODER5_Pos);

    while (true)
    {
        // Toggle LED
        GPIOA->ODR ^= GPIO_ODR_5;

        // Delay
        for (i = 0U; i < 100000U; ++i)
        {
        }
    }
}


/*
 * Clock configuration for the Nucleo STM32F072RB board
 *
 * HSE input Bypass Mode         -> 8 MHz
 * SYSCLK, AHB, APB1            -> 48 MHz
 * PA8 as MCO with /16 prescaler -> 3 MHz
 */

static void SystemClock_Config()
{
    uint32_t hseStatus = 0U;
    uint32_t pllStatus = 0U;
    uint32_t swStatus  = 0U;
    uint32_t timeout   = 1000000U;

    // -------------------------------------------------------------------------
    // Start HSE in Bypass Mode
    // -------------------------------------------------------------------------

    RCC->CR |= RCC_CR_HSEBYP;
    RCC->CR |= RCC_CR_HSEON;

    // -------------------------------------------------------------------------
    // Wait until HSE is ready
    // -------------------------------------------------------------------------

    do
    {
        hseStatus = RCC->CR & RCC_CR_HSERDY_Msk;
        --timeout;
    }
    while ((hseStatus == 0U) && (timeout > 0U));

    // -------------------------------------------------------------------------
    // Configure PLL
    // HSE (8 MHz) -> PLL -> 48 MHz
    // -------------------------------------------------------------------------

    // Select HSE as PLL input source

    RCC->CFGR &= ~RCC_CFGR_PLLSRC_Msk;
    RCC->CFGR |= (0x02U << RCC_CFGR_PLLSRC_Pos);

    // Set PLL PREDIV = /1

    RCC->CFGR2 = 0x00000000U;

    // Set PLL multiplier = x6
    // 8 MHz × 6 = 48 MHz

    RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;
    RCC->CFGR |= (0x04U << RCC_CFGR_PLLMUL_Pos);

    // -------------------------------------------------------------------------
    // Enable PLL
    // -------------------------------------------------------------------------

    RCC->CR |= RCC_CR_PLLON;

    // Wait until PLL is locked

    do
    {
        pllStatus = RCC->CR & RCC_CR_PLLRDY_Msk;
        --timeout;
    }
    while ((pllStatus == 0U) && (timeout > 0U));

    // -------------------------------------------------------------------------
    // Configure bus prescalers
    // -------------------------------------------------------------------------

    // AHB = SYSCLK / 1

    RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    // APB1 = HCLK / 1

    RCC->CFGR &= ~RCC_CFGR_PPRE_Msk;
    RCC->CFGR |= RCC_CFGR_PPRE_DIV1;

    // -------------------------------------------------------------------------
    // Configure Flash
    // -------------------------------------------------------------------------

    // Enable prefetch buffer
    // Set 1 wait state for 48 MHz operation

    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

    /*
     * ------------------------------------------------------------------------
     * Until this point the MCU is still running from HSI (8 MHz)
     * ------------------------------------------------------------------------
     */

    /*
     * ------------------------------------------------------------------------
     * Switching system clock to PLL (48 MHz)
     * ------------------------------------------------------------------------
     */

    // Select PLL as SYSCLK source

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait until PLL becomes system clock

    do
    {
        swStatus = RCC->CFGR & RCC_CFGR_SWS_Msk;
        --timeout;
    }
    while ((swStatus != RCC_CFGR_SWS_PLL) && (timeout > 0U));

    /*
     * ------------------------------------------------------------------------
     * MCU is now running at 48 MHz
     * ------------------------------------------------------------------------
     */

    // -------------------------------------------------------------------------
    // Configure MCO output on PA8
    // -------------------------------------------------------------------------

    // MCO source = SYSCLK (48 MHz)

    RCC->CFGR &= ~RCC_CFGR_MCO_Msk;
    RCC->CFGR |= RCC_CFGR_MCOSEL_SYSCLK;

    // MCO prescaler = /16
    // 48 MHz / 16 = 3 MHz

    RCC->CFGR &= ~RCC_CFGR_MCOPRE_Msk;
    RCC->CFGR |= RCC_CFGR_MCOPRE_DIV16;

    // -------------------------------------------------------------------------
    // Configure PA8 as MCO output
    // -------------------------------------------------------------------------

    // Enable GPIOA clock

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // PA8 -> Alternate Function mode

    GPIOA->MODER &= ~GPIO_MODER_MODER8_Msk;
    GPIOA->MODER |= (0x02U << GPIO_MODER_MODER8_Pos);

    // AF0 = MCO

    GPIOA->AFR[1] &= ~0x0000000FU;
    GPIOA->AFR[1] |=  0x00000000U;

    // -------------------------------------------------------------------------
    // Update CMSIS global clock variable
    // -------------------------------------------------------------------------

    SystemCoreClockUpdate();
}