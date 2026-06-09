#include <cstdint>

#include "stm32f0xx.h"

int main()
{
    uint32_t i = 0;

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
        for (i = 0; i < 100000; i++)
        {
        }
    }
}