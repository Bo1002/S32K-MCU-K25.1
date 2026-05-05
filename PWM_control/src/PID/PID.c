/*
 * PID.c
 *
 *  Created on: May 5, 2026
 *      Author: BO
 */

#include "PID.h"

float PID_Compute(PID_t *pid, float setpoint, float actual)
{
    float error = setpoint - actual;
    pid->integral += error * pid->dt;


    float derivate = (error - pid->pre_error)/ pid->dt; 

    float output = pid->kp* error + pid->ki * pid->integral + pid->kd*derivate;

    if(output > pid->out_max)
    {
        output = pid->out_max; 
    }else if (output < pid->out_min)
    {
        output = pid->out_min; 
    }

    pid->pre_error = error; 
    
    return output;
}