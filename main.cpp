#include "hal.h"

// Variant = 0x3 => 0011

void set_color(uint color)
{
    HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_SET);
}

void reset_color(uint color)
{
    HAL_GPIO_WritePin(GPIOD, color, GPIO_PIN_RESET);
}

void reset_all_colors()
{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

void reset_all_leds(int *leds_num)
{
    for (int i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_RESET);
    }
}

void init_delay(int delay)
{
    HAL_Delay(delay);
}

void choose_switch(int idx, int *sw_num, int *leds_num)
{
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOE, sw_num[idx]);
    HAL_GPIO_WritePin(GPIOD, leds_num[idx], state);
}

GPIO_PinState get_state(int *sw_num, int idx)
{
    return HAL_GPIO_ReadPin(GPIOE, sw_num[idx]);
}

GPIO_PinState get_n_btn_state()
{
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
}

void play_animation(int *leds_num, int delay, int *sw_num, int *states)
{
    reset_all_leds(leds_num);
    for (int i = 7; i > 0; --i)
    {
        if ((get_state(sw_num, 2) == states[1]) ||
            (get_state(sw_num, 3) == states[1]) ||
            (get_state(sw_num, 1) == states[0]) ||
            (get_state(sw_num, 0) == states[0]))
        {
            reset_all_leds(leds_num);
            return;
        }

        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, leds_num[i - 1], GPIO_PIN_SET);
        init_delay(delay);
        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_RESET);
    }
    for (int i = 1; i < 6; ++i)
    {
        if ((get_state(sw_num, 2) == states[1]) ||
            (get_state(sw_num, 3) == states[1]) ||
            (get_state(sw_num, 1) == states[0]) ||
            (get_state(sw_num, 0) == states[0]))
        {
            reset_all_leds(leds_num);
            return;
        }

        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, leds_num[i + 1], GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, leds_num[i - 1], GPIO_PIN_RESET);
        init_delay(delay);
        HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_RESET);
    }
}

int umain()
{
    // Delay should be 0.5s
    int delay = 500;

    /* ----States--- 
    GPIO_PinState:
        - GPIO_PIN_SET
        - GPIO_PIN_RESET 
    */
    int states[] = {
        GPIO_PIN_SET,
        GPIO_PIN_RESET};

    // Leds under switches
    int leds_num[] = {
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_11,
        GPIO_PIN_12};

    // Switches
    int sw_num[] = {
        GPIO_PIN_4,
        GPIO_PIN_8,
        GPIO_PIN_10,
        GPIO_PIN_12};

    // State colors
    uint green = GPIO_PIN_13;
    uint yellow = GPIO_PIN_14;
    uint red = GPIO_PIN_15;

    // MAIN CYCLE
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            choose_switch(i, sw_num, leds_num);
        }

        if (((get_state(sw_num, 2) == states[0]) && (get_state(sw_num, 3) == states[0])) &&
            ((get_state(sw_num, 0) == states[1]) &&
             (get_state(sw_num, 1) == states[1])))
        {
            reset_color(yellow);
            reset_color(red);
            set_color(green);
            play_animation(leds_num, delay, sw_num, states);
        }
        else
        {
            reset_color(green);
            reset_color(red);
            set_color(yellow);
        }
    }

    return 0;
}