/*
 * LineBuild.c
 *
 *  Created on: Jan 10, 2026
 *      Author: BO
 */

#include "LineBuild.h"



void LineBuilder_Reset(LineBuilder_t *lb)
{
    lb->idx = 0;
}

bool LineBuilder_PushChar(LineBuilder_t *lb, uint8_t ch)
{
    if (ch == '\n')
    {
        lb->buf[lb->idx] = '\0';
        return true;
    }

    if (lb->idx < LINE_MAX_LEN - 1)
    {
        lb->buf[lb->idx++] = ch;
    }
    return false;
}
