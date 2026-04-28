/*
 * FlashJobQueue.h
 *
 *  Created on: Jan 10, 2026
 *      Author: BO
 */

#ifndef QUEUE_FLASH_JOBQUEUE_FLASHJOBQUEUE_H_
#define QUEUE_FLASH_JOBQUEUE_FLASHJOBQUEUE_H_

typedef struct {
    uint32_t address;
    uint8_t  data[32];
    uint8_t  len;
} FlashJob_t;

#define FLASH_JOB_Q_SIZE 8U

typedef struct {
    FlashJob_t jobs[FLASH_JOB_Q_SIZE];
    uint8_t head, tail, count;
} FlashJobQueue_t;

#endif /* QUEUE_FLASH_JOBQUEUE_FLASHJOBQUEUE_H_ */
