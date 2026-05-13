/*
 * APP_ETB.h
 *
 *  Created on: May 13, 2026
 *      Author: BO
 */

#ifndef APP_APP_ETB_H_
#define APP_APP_ETB_H_

#include "ADC.h"
#include "CAN_DR.H"
#include "PWM_Driver.h"
#include "encorder.h"

#include <stdint.h>
void  App_Init(void);        // khởi tạo toàn bộ driver
void  App_RunStep(void);     // gọi mỗi 10ms từ LPIT ISR

void  App_SetTargetRPM(float rpm);   // nhận setpoint từ CAN
float App_GetActualRPM(void);        // đọc tốc độ thực
void  SetTimeTick(uint16_t time_s);

#endif /* APP_APP_ETB_H_ */
