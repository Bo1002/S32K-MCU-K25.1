#include <S32K144.h>
#include "NVIC.h"
#define FLEXCAN_RX 12
#define FLEXCAN_TX 13   

uint8_t data[] = {0,1,2,3,4,5,6,7};
volatile uint8_t rx_data[8] = {0}; 
volatile uint8_t rx_flag = 0;


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

    /*CLEAR ALL BIT*/
    for  (uint8_t i = 0; i < 128; i++)
    {
        IP_FLEXCAN0->RAMn[i] = 0; 
    }
    
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
    IP_FLEXCAN0->IFLAG1 = 0x00000001;
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

void CAN_RECEIVED(uint16_t filter_ID)
{

    /* CS = EMPTY (CODE - 0X4), DLC = 8*/
    IP_FLEXCAN0->RAMn[4] = 0x04080000;    
    /*MB1 : ID = filter_id shift 18 */
    IP_FLEXCAN0->RAMn[5] = (filter_ID << 18);
}

void CAN0_ORed_0_15_MB_IRQHandler(void)
{
    /*Watch IFLAG bit 1  (MB1)*/
    if(!(IP_FLEXCAN0->IFLAG1 & (1 << 1)))
    {
    /* READ data from MB1*/
    uint32_t word0 = IP_FLEXCAN0->RAMn[6];
    uint32_t word1 = IP_FLEXCAN0->RAMn[7];

    rx_data[0] = (word0 >> 24) & 0xFF;
    rx_data[1] = (word0 >> 16) & 0xFF;
    rx_data[2] = (word0 >> 8) & 0xFF;
    rx_data[3] = (word0 ) & 0xFF;
    rx_data[4] = (word1 >> 24) & 0xFF;
    rx_data[5] = (word1 >> 16) & 0xFF;
    rx_data[6] = (word1 >> 8) & 0xFF;
    rx_data[7] = (word1 ) & 0xFF;

    IP_FLEXCAN0->IFLAG1 = (1 << 1);
    rx_flag =1;
    }
};

int main()
{
    /* Initialize CAN interface */
    SPLL_SOSC_80Mhz();
    CAN_BIT_TIMING();
    CAN_SEND(0x123,data, sizeof(data));
    
    NVIC_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);

    CAN_RECEIVE(0x123);   // chỉ nhận ID 0x123
    while(1)
    {
        if(rx_flag)
        {
            rx_flag = 0;
            /*data executed in hear*/
        }
    }
    
    return 0;
}
