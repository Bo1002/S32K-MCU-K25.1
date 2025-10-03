#include "S32K144.h"

#define RED_D    15
#define GREEN_D  16
#define BLUE_D   0

#define ADC_MAX    4095
#define VREFH_MV   5000

/*========================= Init SOSC (External Crystal) =========================*/
void SOSC_Init(void)
{
    /* Unlock và config SOSC */
	IP_SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1) | SCG_SOSCDIV_SOSCDIV2(1);
	IP_SCG->SOSCCFG =0x24;
    while (IP_SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK);

    /* SOSCCFG: RANGE=2 (1–8MHz), EREFS=1 (dùng external crystal) */


    /* Bật SOSC */
    IP_SCG->SOSCCSR = 0x1;

    /* Chia clock SOSC ra SOSCDIV1 và SOSCDIV2 */

    /* Chờ SOSC ổn định */
    while (!(IP_SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));
}

/*========================= Init ADC0 =========================*/
void ADC0_Init(void)
{
    /* Bật clock cho PORTC và ADC0 */
    IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_ADC0_INDEX] = PCC_PCCn_PCS(1) | PCC_PCCn_CGC_MASK;

    /* Cấu hình PTC4 về chế độ analog (ADC0_SE10) */
    IP_PORTC->PCR[14] |= PORT_PCR_MUX(0);

    /* ADC config */
    IP_ADC0->CFG1 = ADC_CFG1_MODE(1) | ADC_CFG1_ADIV(1)| ADC_CFG1_ADICLK(0);

    IP_ADC0->CFG2 = ADC_CFG2_SMPLTS(12);
    IP_ADC0->SC2  = 0;
    IP_ADC0->SC3  = 0;
}

/*========================= Đọc 1 kênh ADC =========================*/
uint16_t ADC0_Read(uint8_t ch)
{
	/*chose channel*/
    IP_ADC0->SC1[0] = ADC_SC1_ADCH(ch);
    while(!(IP_ADC0->SC1[0] & ADC_SC1_COCO_MASK));
    return IP_ADC0->R[0];
}

/*========================= Init LED GPIO =========================*/
void LED_Init(void)
{
    IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;

    IP_PORTD->PCR[RED_D]   = PORT_PCR_MUX(1);
    IP_PORTD->PCR[GREEN_D] = PORT_PCR_MUX(1);
    IP_PORTD->PCR[BLUE_D]  = PORT_PCR_MUX(1);

    IP_PTD->PDDR |= (1<<RED_D) | (1<<GREEN_D) | (1<<BLUE_D);

    /*  (active low → set high) */
    IP_PTD->PSOR = (1<<RED_D) | (1<<GREEN_D) | (1<<BLUE_D);
}

/*========================= Main =========================*/
int main(void)
{
	/* init external crystal*/
    SOSC_Init();
    /*Init led*/
    LED_Init();
    /*init ADC0*/
    ADC0_Init();

    while (1)
    {
    	/* read channel (PTC4)*/
        uint16_t adc_raw = ADC0_Read(12);
        uint32_t mv = (uint32_t)adc_raw * VREFH_MV / ADC_MAX;

        /* Reset LED*/
        IP_PTD->PSOR = (1<<RED_D) | (1<<GREEN_D) | (1<<BLUE_D);

        if (mv >= 3750) {
            IP_PTD->PCOR = (1<<RED_D);
        } else if (mv >= 2500) {
            IP_PTD->PCOR = (1<<GREEN_D);
        } else if (mv >= 1250) {
            IP_PTD->PCOR = (1<<BLUE_D);
        }
    }
}
