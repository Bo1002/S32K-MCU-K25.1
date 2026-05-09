/*
 * ADC.c
 *
 *  Created on: May 7, 2026
 *      Author: BO
 */

#include "ADC.h"
#include <S32K144.h>
ARM_ADC_SignalEvent_t Signal_cb = NULL;

int32_t ADC_INIT(ARM_ADC_SignalEvent_t cbvent)
{
    /*enable Port C*/
    IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
    /*Enable ADC */
    IP_PCC->PCCn[PCC_ADC0_INDEX] |= PCC_PCCn_PCS(1) | PCC_PCCn_CGC_MASK;
    /*chose mux mode for pin 14*/
    IP_PORTC->PCR[14] |= PORT_PCR_MUX(0);

    IP_ADC0->CFG1 |= ADC_CFG1_MODE(1) | ADC_CFG1_ADIV(0) |  ADC_CFG1_ADICLK(0);

    IP_ADC0->SC2 = 0;
    IP_ADC0->SC3 = 0;
    IP_ADC0->CFG2 = ADC_CFG2_SMPLTS(12); 
    return 1;
}   

int32_t ADC_READ(uint8_t channel)
{
    IP_ADC0->SC1[0] = ADC_SC1_ADCH(channel);
    while(!(IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK));
    return IP_ADC0->R[0];
}

ADC_SIG Driver_ADC = 
{
    ADC_INIT,
    ADC_READ
};