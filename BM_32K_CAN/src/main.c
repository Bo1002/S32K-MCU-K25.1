#include <S32K144.h>

#define FLEXCAN_RX 12
#define FLEXCAN_TX 13   

void SPLL_SOSC_80Mhz()
{
    /*Set clock divide by 1*/
    while(IP_SCG ->SOSCCSR & SCG_SOSCCSR_LK_MASK);
    IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(0B001) | SCG_SOSCDIV_SOSCDIV2 (0b001);
    /*system enable clock */
    IP_SCG->SOSCCFG |= SCG_SOSCCFG_EREFS_MASK | SCG_SOSCCFG_RANGE(3);

    IP_SCG->SOSCCSR |= SCG_SOSCCSR_SOSCEN_MASK;

    while(!(IP_SCG ->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* wait valid number*/

    /*SPLL config for pushing the speed of clock to 80mhz*/
    while(IP_SCG ->SPLLCSR & SCG_SPLLCSR_LK_MASK);
    IP_SCG ->SPLLCFG |= SCG_SPLLCFG_SOURCE(0) | SCG_SPLLCFG_PREDIV(0) | SCG_SPLLCFG_MULT(4);
    IP_SCG ->SPLLCSR |= SCG_SPLLCSR_SPLLEN_MASK;

    while(!(IP_SCG ->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK));
    IP_SCG->RCCR = (IP_SCG -> RCCR & ~ SCG_RCCR_SCS_MASK)  | SCG_RCCR_SCS(6); 

}

void CAN_ENABLE()
{
    /*enable clock for Flexcan*/
    IP_PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK;
    /*Turn MUX for flexCAN */
    /* CAN RX*/
    IP_PORTA->PCR[FLEXCAN_RX] = PORT_PCR_MUX(5);
    IP_PORTA->PCR[FLEXCAN_TX] = PORT_PCR_MUX(5);
}

void CAN_INIT()
{
    /* Enable Clock Gate for FlexCAN0 */
    CAN_ENABLE();
    /*ENABLE CAN MODULE */
    IP_FLEXCAN0->MCR &= ~ (FLEXCAN_MCR_MDIS_MASK | FLEXCAN_MCR_FRZ_MASK);

    while((IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));

    /* Enable freeze mode*/ 
    IP_FLEXCAN0->MCR |=  FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK; 
    while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));
}

void CAN_BIT_TIMING()
{
    CAN_INIT();
    IP_FLEXCAN0->CTRL1 |= FLEXCAN_CTRL1_PRESDIV(9) | FLEXCAN_CTRL1_PROPSEG(3) 
                       | FLEXCAN_CTRL1_PSEG1(5) | FLEXCAN_CTRL1_PSEG2(4);

    while(IP_FLEXCAN0->MCR & FLEXCAN_MCR_NOTRDY_MASK); 
}

void CAN_SEND()
{
    
}

int main()
{
    /* Initialize CAN interface */
    SPLL_SOSC_80Mhz();
    CAN_BIT_TIMING();
    
    /* Main loop */
    while(1)
    {
        /* CAN is now running and ready for messages */
    }
    
    return 0;
}
