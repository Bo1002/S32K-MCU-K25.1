/*
 * SrecLineQueue.c
 *
 *  Created on: Jan 10, 2026
 *      Author: BO
 */


#include "SrecLineQueue.h"
#include <string.h>

void SrecLineQueue_Init(SrecLineQueue_t *q)
{
    q->head = 0;
    q->tail = 0;
}

bool SrecLineQueue_Push(SrecLineQueue_t *q, const char *line)
{
    uint8_t next = (q->head + 1) % SREC_LINE_Q_SIZE;
    if (next == q->tail) return false;

    strcpy(q->lines[q->head], line);
    q->head = next;
    return true;
}

bool SrecLineQueue_Pop(SrecLineQueue_t *q, char *out)
{
    if (q->head == q->tail) return false;

    strcpy(out, q->lines[q->tail]);
    q->tail = (q->tail + 1) % SREC_LINE_Q_SIZE;
    return true;
}
