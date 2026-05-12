/*
 * encorder.c
 *
 *  Created on: May 12, 2026
 *      Author: BO
 */


#include "encorder.h"
#include <S32K144.h>

static uint16_t prev_count = 0;

void ENCODER_Init(void)
{
    // 1. Enable clock PORTB và FTM1
    IP_PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_FTM1_INDEX]  |= PCC_PCCn_CGC_MASK;

    // 2. Set PTB0 = FTM1_CH0 (Phase A), PTB1 = FTM1_CH1 (Phase B)
    IP_PORTB->PCR[0] = PORT_PCR_MUX(2);
    IP_PORTB->PCR[1] = PORT_PCR_MUX(2);

    // 3. Cấu hình FTM1
    IP_FTM1->MODE  |= FTM_MODE_WPDIS_MASK;   // tắt write protection
    IP_FTM1->CNTIN  = 0x0000;
    IP_FTM1->MOD    = 0xFFFF;
    IP_FTM1->CNT    = 0;

    // 4. Bật Quadrature Decoder
    IP_FTM1->QDCTRL = FTM_QDCTRL_QUADEN_MASK;

    // 5. Enable module (bắt buộc)
    IP_FTM1->SC = FTM_SC_CLKS(1);
}

int16_t ENCODER_GetDelta(void)
{
    uint16_t current = IP_FTM1->CNT;
    int16_t delta = (int16_t)(current - prev_count);
    prev_count = current;
    return delta;
}

uint8_t ENCODER_GetDir(void)
{
    return (IP_FTM1->QDCTRL & FTM_QDCTRL_QUADIR_MASK) ? 1 : 0;
}

void ENCODER_ResetCount(void)
{
    IP_FTM1->CNT = 0;
    prev_count   = 0;
}

