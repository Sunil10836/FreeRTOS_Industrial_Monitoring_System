#include "ring_buffer.h"

void RingBuffer_Init(RingBuffer_t *pRingBuffer)
{
    pRingBuffer->Head = 0;
    pRingBuffer->Tail = 0;
}

uint8_t RingBuffer_IsEmpty(RingBuffer_t *pRingBuffer)
{
    return (pRingBuffer->Head == pRingBuffer->Tail);
}

uint8_t RingBuffer_IsFull(RingBuffer_t *pRingBuffer)
{
    return (((pRingBuffer->Head + 1U) % RING_BUFFER_SIZE) == pRingBuffer->Tail);
}

uint8_t RingBuffer_Put(RingBuffer_t *pRingBuffer, uint8_t data)
{
    uint16_t nextHead;

    nextHead = (pRingBuffer->Head + 1U) % RING_BUFFER_SIZE;

    if(nextHead == pRingBuffer->Tail)
    {
        //buffer is Full
        return 0;
    }

    pRingBuffer->Buffer[pRingBuffer->Head] = data;

    pRingBuffer->Head = nextHead;
    
    return 1;
}

uint8_t RingBuffer_Get(RingBuffer_t *pRingBuffer, uint8_t *data)
{
    if(RingBuffer_IsEmpty(pRingBuffer))
    {
        /* Buffer is Empty */
        return 0;
    }

    *data = pRingBuffer->Buffer[pRingBuffer->Tail];

    pRingBuffer->Tail = (pRingBuffer->Tail + 1U) % RING_BUFFER_SIZE;

    return 1;
}

uint16_t RingBuffer_Available(RingBuffer_t *pRingBuffer)
{
    if(pRingBuffer->Head >= pRingBuffer->Tail)
    {
        return (pRingBuffer->Head - pRingBuffer->Tail);
    }
    else
    {
        return (RING_BUFFER_SIZE - pRingBuffer->Tail + pRingBuffer->Head);
    }
}

void RingBuffer_Flush(RingBuffer_t *pRingBuffer)
{
    pRingBuffer->Head = 0;
    pRingBuffer->Tail = 0;
}