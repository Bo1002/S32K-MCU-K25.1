/*
 * SrecLineQueue.h
 *
 *  Created on: Jan 10, 2026
 *      Author: BO
 */

#ifndef QUEUE_SREC_LINE_QUEUE_SRECLINEQUEUE_H_
#define QUEUE_SREC_LINE_QUEUE_SRECLINEQUEUE_H_

#include <stdbool.h>
#include <stdint.h>
#define SREC_LINE_Q_SIZE 8U
#define SREC_MAX_LINE_LEN 256U


typedef struct {
    char lines[SREC_LINE_Q_SIZE][SREC_MAX_LINE_LEN];
    uint8_t head;
    uint8_t tail;
} SrecLineQueue_t;

void SrecLineQueue_Init(SrecLineQueue_t *q);
bool SrecLineQueue_Push(SrecLineQueue_t *q, const char *line);

bool SrecLineQueue_Pop(SrecLineQueue_t *q, char *out);


#endif /* QUEUE_SREC_LINE_QUEUE_SRECLINEQUEUE_H_ */
