#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define RING_BUFFER_SIZE    128U

typedef struct
{
    uint8_t Buffer[RING_BUFFER_SIZE];

    volatile uint16_t Head;
    volatile uint16_t Tail;

}RingBuffer_t;

/* Initialization */
void RingBuffer_Init(RingBuffer_t *pRingBuffer);

/* Write one byte */
uint8_t RingBuffer_Put(RingBuffer_t *pRingBuffer, uint8_t data);

/* Read one byte */
uint8_t RingBuffer_Get(RingBuffer_t *pRingBuffer, uint8_t *data);

/* Status */
uint8_t RingBuffer_IsEmpty(RingBuffer_t *pRingBuffer);
uint8_t RingBuffer_IsFull(RingBuffer_t *pRingBuffer);
uint16_t RingBuffer_Available(RingBuffer_t *pRingBuffer);

void RingBuffer_Flush(RingBuffer_t *pRingBuffer);

#endif /* RING_BUFFER_H */
