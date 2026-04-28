#pragma once

#include "stm32f072xb.h"
#include <stdint.h>

namespace gpio {

void enable_port_a();
void set_output(GPIO_TypeDef *port, uint8_t pin);
void toggle(GPIO_TypeDef *port, uint8_t pin);

} // namespace gpio