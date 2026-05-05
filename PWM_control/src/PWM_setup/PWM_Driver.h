/**
 * @file PWM_Driver.h
 * @author Nguyen Dinh Minh Vuong (nguyendinhminhvuong1002@gmail.com)
 * @brief This product use to control the speed of the motor
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #ifndef PWM_DRIVER_H
 #define PWM_DRIVER_H

 #include <stdint.h>


typedef void (*ARM_PWM_SignalEvent_t) (uint32_t event);

typedef struct {
    int32_t (*Initialize) (ARM_PWM_SignalEvent_t cb_event);
    int32_t (*SetDuty)    (uint8_t channel, uint8_t percent);
    int32_t (*SetFreq)    (uint32_t freq_hz);
    int32_t (*Start)      (uint8_t channel);
    int32_t (*Stop)       (uint8_t channel);
} ARM_DRIVER_PWM;




 #endif