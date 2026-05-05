/*
 * PWM_Driver.c
 *
 *  Created on: May 4, 2026
 *      Author: BO
 */

#include "PWM_Driver.h"
#include <S32K144.h>

ARM_PWM_SignalEvent_t PWM_Cb_event = NULL ;

/******************Protocal********************************************
 * 
 *********************************************************************/

/***********************************implement************************* 
 *********************************************************************/


static int32_t PWM_Initialize(ARM_PWM_SignalEvent_t cb_event)
{
    IP_PCC->PCCn[PCC_FTM0_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;

    IP_PORTD->PCR[1] = PORT_PCR_MUX(2);

    IP_FTM0->SC     = 0;
    IP_FTM0->CNTIN  = 0;
    IP_FTM0->MOD    = 9999;

    IP_FTM0->CONTROLS[0].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
    IP_FTM0->CONTROLS[0].CnV  = 0;

    IP_FTM0->SC = FTM_SC_CLKS(1) | FTM_SC_PS(3);

    return 0;

}
static int32_t PWM_SetDuty(uint8_t channel, uint8_t percent) 
{
    IP_FTM0->CONTROLS[channel].CnV = (9999 * percent) / 100;
    return 0;
}
static int32_t PWM_SetFreq(uint32_t freq_hz) 
{
    IP_FTM0->MOD = (10000000 / freq_hz) - 1;  /* clock FTM = 10MHz */
    return 0;
}

static int32_t PWM_Start(uint8_t channel)
{
    IP_FTM0->CONTROLS[channel].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
    return 0;
}

static int32_t PWM_Stop(uint8_t channel)
{
    IP_FTM0->CONTROLS[channel].CnV = 0;
    return 0;
}

ARM_DRIVER_PWM Driver_PWM = {
    PWM_Initialize,
    PWM_SetDuty,
    PWM_SetFreq,
    PWM_Start,
    PWM_Stop
};



