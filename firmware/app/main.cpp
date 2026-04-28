#include "gpio.hpp"
#include "stm32f072xb.h"

constexpr int led_pin = 5;
constexpr int delay_cycles = 500000;

auto main() -> int {

    gpio::enable_port_a();
    gpio::set_output(GPIOA, led_pin);

    while (true) {
        gpio::toggle(GPIOA, led_pin);

        for (volatile int i = 0; i < delay_cycles; ++i) {
        }
    }
}