/*
 * PID.h
 *
 *  Created on: May 5, 2026
 *      Author: BO
 */

#ifndef PID_PID_H_
#define PID_PID_H_

typedef struct
{
    float ki, kp, kd;
    float integral;
    float pre_error;
    float dt; /* Loop time */
    float out_max;  /* limit out put max*/
    float out_min; /*limit output min*/
}PID_t;

float PID_Compute (PID_t* pid, float setpoint, float actual); 

#endif /* PID_PID_H_ */
