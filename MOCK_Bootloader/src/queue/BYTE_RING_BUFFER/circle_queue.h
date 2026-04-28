/*
 * circle_queue.h
 *
 *  Created on: Dec 23, 2025
 *      Author: BO
 */

#ifndef QUEUE_CIRCLE_QUEUE_H_
#define QUEUE_CIRCLE_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

#define BYTE_Q_SIZE 256U


/* ByteQueueu _t : buf lưu trữ từng byte, khi uart callback được gọi, mỗi lần có uart sent or receive */
typedef struct {
    uint8_t buf[BYTE_Q_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} ByteQueue_t;


void ByteQueue_Init(ByteQueue_t *q);
bool ByteQueue_Push(ByteQueue_t *q, uint8_t data);
bool ByteQueue_Pop(ByteQueue_t *q, uint8_t *data);
bool ByteQueue_IsEmpty(const ByteQueue_t *q);

#endif /* QUEUE_CIRCLE_QUEUE_H_ */
