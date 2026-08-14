#include "led.h"

void LED_Init()
{
    GPIO_Handle_t GpioLed;

    GpioLed.pGPIOx = LED_PORT;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = LED_PIN;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&GpioLed);
}

void LED_On()
{
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_SET);
}

void LED_Off()
{
    GPIO_WriteToOutputPin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
}

void LED_Toggle()
{
    GPIO_ToggleOutputPin(LED_PORT, LED_PIN);
}