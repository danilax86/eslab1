#include "hal.h"

// Variant = 21

void set_color(uint color)
{
    HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_SET);
}

void res_color(uint color)
{
    HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_RESET);
}

void init_delay(int delay)
{
    HAL_Delay(delay);
}

void use_switch

int umain()
{
    // Delay should be 0.5s
    int delay = 500;

    // Leds under switches
    int leds_num[] = {
            GPIO_PIN_3,
            GPIO_PIN_4,
            GPIO_PIN_5,
            GPIO_PIN_6,
            GPIO_PIN_8,
            GPIO_PIN_9,
            GPIO_PIN_11,
            GPIO_PIN_12
    };

    // Switches
    int sw_num[] = {
            GPIO_PIN_4,
            GPIO_PIN_8,
            GPIO_PIN_10,
            GPIO_PIN_12
    };

    // State colors
    uint green = GPIO_PIN_13;
    uint yellow = GPIO_PIN_14;
    uint red = GPIO_PIN_15;

    while (1)
    // MAIN CYCLE
    {
        /* code */
    }
    

    for (int i = 0; i < 8; i++)
    {
        blink(red, delay);
        blink(green, delay);
    }

    return 0;
}