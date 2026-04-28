#include "gpio.hpp"

namespace gpio {

// Enable the clock for GPIO port A
void enable_port_a() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
}

// Set the mode of a GPIO pin to output
void set_output(GPIO_TypeDef *port, uint8_t pin) {
    port->MODER |= (1 << (pin * 2));
}

// Toggle the state of a GPIO pin
void toggle(GPIO_TypeDef *port, uint8_t pin) {
    port->ODR ^= (1 << pin);
}

} // namespace gpio