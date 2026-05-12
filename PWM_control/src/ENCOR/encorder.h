/*
 * encorder.h
 *
 *  Created on: May 12, 2026
 *      Author: BO
 */

// Encoder.h
#ifndef ENCODER_H_
#define ENCODER_H_
#include <stdint.h>

void     ENCODER_Init(void);
int16_t  ENCODER_GetDelta(void);   // delta count từ lần đọc trước
uint8_t  ENCODER_GetDir(void);     // 1=thuận, 0=nghịch
void     ENCODER_ResetCount(void);

#endif
