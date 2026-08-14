
#ifndef USART_RING_BUFFER_H
#define USART_RING_BUFFER_H

#include "stm32f446xx.h"
#include "stm32f446xx_usart_driver.h"

/* Ring Buffer APIs*/
void RB_USART_RingBufferInit(USART_Handle_t *pUSARTHandle);
void RB_USART_WriteByte(USART_Handle_t *pUSARTHandle, uint8_t data);
void RB_USART_WriteString(USART_Handle_t *pUSARTHandle, const char *str);
void RB_USART_IRQHandling(USART_Handle_t *pUSARTHandle);
uint8_t RB_USART_ReadByte(USART_Handle_t *pUSARTHandle, uint8_t *data);
void RB_USART_StartReception(USART_Handle_t *pUSARTHandle);
uint8_t RB_USART_ReadLine(USART_Handle_t *pUSARTHandle, char *buffer, uint16_t maxLen);


#endif