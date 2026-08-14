/**
 * @file    uart.h
 * @author  Sunil Sutar
 * @brief   UART driver interface.
 *
 * @details
 * Provides UART initialization and communication APIs used
 * by the Industrial Monitoring System.
 *
 * UART is primarily used for:
 *      - Debug messages
 *      - Alarm messages
 *      - Logger output
 *      - System status
 *      - Error reporting
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f446xx.h"
#include "string.h"

void USART2_PinConfig();
void USART2_Init();

extern USART_Handle_t UART2Handle;

#endif
