/*
 * LineBuild.h
 *
 *  Created on: Jan 10, 2026
 *      Author: BO
 */

#ifndef QUEUE_LINE_BUILDER_LINEBUILD_H_
#define QUEUE_LINE_BUILDER_LINEBUILD_H_
#include <stdbool.h>
#include <stdint.h>
#define LINE_MAX_LEN 128

typedef struct {
    char buf[LINE_MAX_LEN];
    uint16_t idx;
} LineBuilder_t;

void LineBuilder_Reset(LineBuilder_t *lb);

bool LineBuilder_PushChar(LineBuilder_t *lb, uint8_t ch);


#endif /* QUEUE_LINE_BUILDER_LINEBUILD_H_ */
