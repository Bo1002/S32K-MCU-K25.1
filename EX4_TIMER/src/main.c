#include "S32K144.h"
#include "clock.h"

void LPIT0_Ch0_IRQHandler(void)
{
    if (IP_LPIT0->MSR & LPIT_MSR_TIF0_MASK)
    {
        IP_LPIT0->MSR |= LPIT_MSR_TIF0_MASK;  // clear flag
        IP_PTD->PTOR = (1 << 15);             // toggle LED đỏ
    }
}

int main(void)
{
    SOSC_init_8MHz();
    SPLL_init_160MHz();
    NormalRUNmode_80MHz();



    /* Enable clock for LPIT */
    IP_PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6) | PCC_PCCn_CGC_MASK;

    /* Enable module */
    IP_LPIT0->MCR = LPIT_MCR_M_CEN_MASK;

    /* Load 3s (40MHz x 3s - 1) */
    IP_LPIT0->TMR[0].TVAL = (uint32_t)(40000000U * 3 - 1U);

    /* Enable interrupt for channel 0 */
    IP_LPIT0->MIER = LPIT_MIER_TIE0_MASK;

    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(LPIT0_Ch0_IRQn);
    NVIC_SetPriority(LPIT0_Ch0_IRQn, 2U);

    /* Start timer */
    IP_LPIT0->TMR[0].TCTRL = LPIT_TMR_TCTRL_T_EN_MASK;

    /* Configure LED pin */
    IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PORTD->PCR[15] = PORT_PCR_MUX(1);
    IP_PTD->PDDR |= (1 << 15);
    IP_PTD->PSOR = (1 << 15);

    while (1)
    {
        /* Main loop idle */
    }
}
