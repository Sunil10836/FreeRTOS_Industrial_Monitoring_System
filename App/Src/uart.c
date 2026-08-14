/**
 * @file    uart.c
 * @author  Sunil Sutar
 * @brief   UART driver implementation.
 *
 * @details
 * Implements the UART communication functions used by the
 * Industrial Monitoring System.
 *
 * Features:
 *      - UART initialization
 *      - Character transmission
 *      - String transmission
 *      - Debug/status output
 *
 * The UART driver provides the communication layer used by
 * application tasks for diagnostic and monitoring messages.
 */

#include "uart.h"

USART_Handle_t UART2Handle;

void USART2_PinConfig()
{
    GPIO_Handle_t usart_gpios;
    
    usart_gpios.pGPIOx = GPIOA;
    usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF7;

    //USART2_Tx : PA2
    usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_2;
    GPIO_Init(&usart_gpios);

    //USART2_Rx : PA3
    usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
    GPIO_Init(&usart_gpios);
}

void USART2_Init()
{
    /* Configure USART2 GPIO */
    USART2_PinConfig();

    /* Configure USART2 */
    UART2Handle.pUSARTx = USART2;
    UART2Handle.USART_Config.UART_BaudRate = USART_STD_BAUD_115200;
    UART2Handle.USART_Config.UART_Mode = USART_MODE_TXRX;
    //UART2Handle.USART_Config.UART_Mode = USART_MODE_ONLY_TX;
    UART2Handle.USART_Config.UART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
    UART2Handle.USART_Config.UART_WordLength = USART_WORDLEN_8BITS;
    UART2Handle.USART_Config.UART_NoOfStopBits = USART_STOPBITS_1;
    UART2Handle.USART_Config.UART_ParityControl = USART_PARITY_DISABLE;

    USART_Init(&UART2Handle);
}