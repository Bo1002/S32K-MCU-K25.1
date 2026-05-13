/*
 * APP_ETB.c
 *
 *  Created on: May 13, 2026
 *      Author: BO
 */

#include "APP_ETB.h"
#include "S32K144.h"
#include "NVIC.h"
/********MACRO*******/
#define  ADC_MAX     4095u
#define  RPM_MAX     7800u
#define  ADC_Channel 12
#define SPLL_ClKKDIV2   40000000.0f

/**********Protocal*************/
void Lpit_Init(void); 
void LPIT0_Ch0_IRQHandler(void);
/*************implement***************/

void Lpit_Init(void)
{
       /* Enable clock for LPIT */
    IP_PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6) | PCC_PCCn_CGC_MASK;
    /* Enable module */
    IP_LPIT0->MCR = LPIT_MCR_M_CEN_MASK;

}

void  SetTimeTick(uint16_t time_s)
{
    Lpit_Init(); 
    IP_LPIT0->TMR[0].TVAL = (SPLL_ClKKDIV2/time_s) - 1u;
    IP_LPIT0->MIER |= LPIT_MIER_TIE0_MASK;
    NVIC_EnableIRQ(LPIT0_Ch0_IRQn);
    NVIC_SetPriority(LPIT0_Ch0_IRQn,1);
    IP_LPIT0->TMR[0].TCTRL   |= LPIT_TMR_TCTRL_T_EN_MASK;
}




void LPIT0_Ch0_IRQHandler(void)
{
    if(IP_LPIT0->MSR  & LPIT_MSR_TIF0_MASK)
    {
        IP_LPIT0->MSR &= ~LPIT_MSR_TIF0_MASK;
        App_RunStep();
    }
}



extern ARM_DRIVER_CAN ;

void  App_Init(void)
{

}

