#include "hal.h"

// Variant = 0x3 => 0011

// Delay should be 0.5s
unsigned int delay = 500;

// Leds under switches
unsigned int leds_num[] = {
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_11,
    GPIO_PIN_12};

// Switches
unsigned int sw_num[] = {
    GPIO_PIN_4,
    GPIO_PIN_8,
    GPIO_PIN_10,
    GPIO_PIN_12};

void reset_all_leds()
{
    HAL_GPIO_WritePin(GPIOD, leds_num[0], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[1], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[2], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[3], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[4], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[5], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[6], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[7], GPIO_PIN_RESET);
}

void reset_last_leds()
{
    HAL_GPIO_WritePin(GPIOD, leds_num[4], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[5], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[6], GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, leds_num[7], GPIO_PIN_RESET);
}

void red()
{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
}

void green()
{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

void yellow()
{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
}

bool check()
{
    return HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_RESET &&
           HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8) == GPIO_PIN_RESET &&
           HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10) == GPIO_PIN_SET &&
           HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12) == GPIO_PIN_SET;
}

void stop_animation()
{
    red();
    HAL_Delay(delay);
    GPIO_PinState state = GPIO_PIN_SET;
    while (state == GPIO_PIN_SET)
    {
        state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
        if (!check())
            return;
    }
    green();
}

void play_animation()
{
    int i = 7;
    int j = 1;

    while (true)
    {
        if (i > 0)
        {
            HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, leds_num[i - 1], GPIO_PIN_SET);
            HAL_Delay(delay);
            HAL_GPIO_WritePin(GPIOD, leds_num[i], GPIO_PIN_RESET);
            --i;
        }
        if (i == 0)
        {
            HAL_GPIO_WritePin(GPIOD, leds_num[j], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, leds_num[j + 1], GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOD, leds_num[j - 1], GPIO_PIN_RESET);
            HAL_Delay(delay);
            HAL_GPIO_WritePin(GPIOD, leds_num[j], GPIO_PIN_RESET);
            ++j;
            if (j == 6)
            {
                i = 7;
                j = 1;
            }
        }
        if (!check())
            return;

        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET)
            stop_animation();
    }
}

void sw_status_output()
{
    for (int i = 0; i < 4; i++)
    {
        GPIO_PinState state = HAL_GPIO_ReadPin(GPIOE, sw_num[i]);
        HAL_GPIO_WritePin(GPIOD, leds_num[i], state);
    }
}

int umain()
{
    while (true)
    {
        if (check())
        {
            reset_all_leds();
            green();
            play_animation();
        }
        else
        {
            reset_last_leds();
            yellow();
            sw_status_output();
        }
    }
    return 0;
}