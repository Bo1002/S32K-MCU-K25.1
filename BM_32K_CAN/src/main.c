#include <S32K144.h>

#define FLEXCAN_RX 12
#define FLEXCAN_TX 13   

uint8_t *data = {0,1,2,3,4,5,6,7};

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
    IP_FLEXCAN0->MCR =  FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK; 
    while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));
}

void CAN_BIT_TIMING()
{
    CAN_INIT();
    IP_FLEXCAN0->CTRL1 |= FLEXCAN_CTRL1_PRESDIV(9) | FLEXCAN_CTRL1_PROPSEG(3) 
                       | FLEXCAN_CTRL1_PSEG1(5) | FLEXCAN_CTRL1_PSEG2(4);

    IP_FLEXCAN0->MCR &=  ~(FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK); 
    while(IP_FLEXCAN0->MCR & FLEXCAN_MCR_NOTRDY_MASK); 
}

void CAN_SEND(uint16_t id, uint8_t *data, uint8_t len)
{
    /*INACTIVE- Block MB out of bus*/
    IP_FLEXCAN0->RAMn[0] = 0X08000000;

    /*random chose ID, ID in Stand frame allow from 0x000 -> 0x7FF*/
    IP_FLEXCAN0->RAMn[1] = (id << 18);

    /*we chose DLC = 8byte so byte 0 , 1, 2, 3 */ 
    IP_FLEXCAN0->RAMn[2] = ((data[0] << 24)| (data[1] << 16) | (data[2] << 8) | data[3] );
    /*byte 4, 5, 6, 7 */
    IP_FLEXCAN0->RAMn[3] = ((data[4] << 24)| (data[5] << 16) | (data[6] << 8) | data[7] );

    /*IN CODE: SET DLC 0b1000, DATA = 0b1100 */
    IP_FLEXCAN0->RAMn[0] = 0x0C080000;

}

int main()
{
    /* Initialize CAN interface */
    SPLL_SOSC_80Mhz();
    CAN_BIT_TIMING();
    CAN_SEND(0x123,data, 8);
    /* Main loop */
    while(1)
    {
        /* CAN is now running and ready for messages */
    }
    
    return 0;
}
