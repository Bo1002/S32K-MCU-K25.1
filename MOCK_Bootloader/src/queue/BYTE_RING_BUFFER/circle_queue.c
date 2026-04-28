/*
 * circle_queue.c
 *
 *  Created on: Dec 23, 2025
 *      Author: BO
 */

#include <BYTE_RING_BUFFER/circle_queue.h>

void ByteQueue_Init(ByteQueue_t *q)
{
    q->head = 0;
    q->tail = 0;
}

bool ByteQueue_Push(ByteQueue_t *q, uint8_t data)
{
    uint16_t next = (q->head + 1U) % BYTE_Q_SIZE;
    if (next == q->tail) return false; // full

    q->buf[q->head] = data;
    q->head = next;
    return true;
}

bool ByteQueue_Pop(ByteQueue_t *q, uint8_t *data)
{
    if (q->head == q->tail) return false;

    *data = q->buf[q->tail];
    q->tail = (q->tail + 1U) % BYTE_Q_SIZE;
    return true;
}

bool ByteQueue_IsEmpty(const ByteQueue_t *q)
{
    return (q->head == q->tail);
}

