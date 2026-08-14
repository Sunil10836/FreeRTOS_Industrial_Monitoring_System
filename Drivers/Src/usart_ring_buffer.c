
#include "usart_ring_buffer.h"

/*******************************************
 * Ring Buffer
 *******************************************/
static void RB_USART_HandleTXEInterrupt(USART_Handle_t *pUSARTHandle);
static void RB_USART_HandleTCInterrupt(USART_Handle_t *pUSARTHandle);
static void RB_USART_HandleRXNEInterrupt(USART_Handle_t *pUSARTHandle);

__attribute__((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t AppEv);

void RB_USART_RingBufferInit(USART_Handle_t *pUSARTHandle)
{
    RingBuffer_Init(&pUSARTHandle->TxRingBuffer);
    RingBuffer_Init(&pUSARTHandle->RxRingBuffer);
}

static void RB_USART_HandleTXEInterrupt(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1, temp2;
    uint8_t data;

    /* Check TXE flag */
    temp1 = pUSARTHandle->pUSARTx->SR & (1 << USART_SR_TXE);

    /* Check TXE interrupt enable */
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1 << USART_CR1_TXEIE);

    if(temp1 && temp2)
    {
        /* Get one byte from TX ring buffer */
        if(RingBuffer_Get(&pUSARTHandle->TxRingBuffer, &data))
        {
            /* Send byte */
            pUSARTHandle->pUSARTx->DR = data;
        }
        else
        {
            /* Buffer empty - disable TXE interrupt */
            pUSARTHandle->pUSARTx->CR1 &= ~(1 << USART_CR1_TXEIE);

            /* Enable TC interrupt for final completion */
            pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);
        }
    }
}

static void RB_USART_HandleTCInterrupt(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1;
    uint32_t temp2;

    temp1 = pUSARTHandle->pUSARTx->SR & (1U << USART_SR_TC);
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1U << USART_CR1_TCIE);

    if(temp1 && temp2)
    {
        /* Disable TC interrupt */
        pUSARTHandle->pUSARTx->CR1 &= ~(1U << USART_CR1_TCIE);

        /* Optional callback */
        USART_ApplicationEventCallback(pUSARTHandle, USART_EVENT_TX_CMPLT);
    }
}

static void RB_USART_HandleRXNEInterrupt(USART_Handle_t *pUSARTHandle)
{
    uint32_t temp1, temp2;
    uint8_t data;

    /* Check RXNE flag */
    temp1 = pUSARTHandle->pUSARTx->SR & (1U << USART_SR_RXNE);

    /* Check RXNE interrupt enable */
    temp2 = pUSARTHandle->pUSARTx->CR1 & (1U << USART_CR1_RXNEIE);

    if(temp1 && temp2)
    {
        /* Read received byte (clears RXNE) */
        data = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0xFFU);

        /* Store in RX Ring Buffer */
        RingBuffer_Put(&pUSARTHandle->RxRingBuffer, data);
    }
}

void RB_USART_IRQHandling(USART_Handle_t *pUSARTHandle)
{
    /**************************************************************
     * Check for TXE Flag
     **************************************************************/
    RB_USART_HandleTXEInterrupt(pUSARTHandle);

    /**************************************************************
     * Check for TC Flag
    **************************************************************/
    RB_USART_HandleTCInterrupt(pUSARTHandle);

    /**************************************************************
     * Check for RXNE Flag
    **************************************************************/
    RB_USART_HandleRXNEInterrupt(pUSARTHandle);
}

void RB_USART_WriteByte(USART_Handle_t *pUSARTHandle, uint8_t data)
{
    /* Wait if TX buffer is full */
    while(!RingBuffer_Put(&pUSARTHandle->TxRingBuffer, data));

    /* Start transmission */
    pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_TXEIE);
}

void RB_USART_WriteString(USART_Handle_t *pUSARTHandle, const char *str)
{
    while(*str)
    {
        RB_USART_WriteByte(pUSARTHandle, (uint8_t)*str);

        str++;
    }
}

uint8_t RB_USART_ReadByte(USART_Handle_t *pUSARTHandle, uint8_t *data)
{
    return RingBuffer_Get(&pUSARTHandle->RxRingBuffer, data);
}

void RB_USART_StartReception(USART_Handle_t *pUSARTHandle)
{
    pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_RXNEIE);
}

uint8_t RB_USART_ReadLine(USART_Handle_t *pUSARTHandle, char *buffer, uint16_t maxLen)
{
    static uint16_t index = 0;
    uint8_t ch;

    while(RB_USART_ReadByte(pUSARTHandle, &ch))
    {
        /* End of line */
        if((ch == '\r') || (ch == '\n'))
        {
            if(index > 0)
            {
                buffer[index] = '\0';
                index = 0;
                return 1;
            }
            continue;
        }

        if(index < (maxLen - 1))
        {
            buffer[index++] = ch;
        }
        else
        {
            buffer[index] = '\0';
            index = 0;
            return 1;
        }
    }

    return 0;
}
