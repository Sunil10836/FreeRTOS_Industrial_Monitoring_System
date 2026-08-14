#ifndef LED_H_
#define LED_H_

#include "stm32f446xx.h"

#define LED_PIN     GPIO_PIN_5
#define LED_PORT    GPIOA

void LED_Init();
void LED_On();
void LED_Off();
void LED_Toggle();

#endif
