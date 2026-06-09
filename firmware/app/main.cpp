#include <cstdint>

constexpr uint32_t DELAY_ON  = 20000;
constexpr uint32_t DELAY_OFF = 100000;

int main()
{
    uint32_t i = 0;
    uint32_t j = 0;

    uint8_t state = 0;

    *reinterpret_cast<volatile uint32_t*>(0x40021014) |= (1U << 17U);

    *reinterpret_cast<volatile uint32_t*>(0x48000000) &= ~(0x3U << 10U);
    *reinterpret_cast<volatile uint32_t*>(0x48000000) |=  (0x1U << 10U);

    while (true)
    {
        switch (state)
        {
            case 0:
            {
                *reinterpret_cast<volatile uint32_t*>(0x48000014) &= ~0x20U;

                ++i;

                if (i > DELAY_OFF)
                {
                    i = 0;
                    ++j;
                    state = 1;
                }
                break;
            }

            case 1:
            {
                *reinterpret_cast<volatile uint32_t*>(0x48000014) |= 0x20U;

                ++i;

                if (i > DELAY_ON)
                {
                    i = 0;
                    state = 0;
                }
                break;
            }
        }
    }
}