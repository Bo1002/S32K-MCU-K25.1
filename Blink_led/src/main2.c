#include "S32k144.h"
#include "NVIC.h"

#include <stdint.h>


/*bật port C */
#define PortC IP_PORTC
#define GpioD IP_PTD
#define PortD IP_PORTD
#define GpioC IP_PTC
uint32_t pinC_13 = 13;
uint32_t pinC_12 = 12;

uint32_t pinD_15 = 15;
uint32_t pinD_16 = 16;



void enable()
{
  IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;
  IP_PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
}


void setup_ledred()
{
   PortD->PCR[pinD_15] |= PORT_PCR_MUX(1U);
   GpioD->PDDR |= (1 << pinD_15);
}

void setup_ledgreen()
{
    PortD->PCR[pinD_16] |= PORT_PCR_MUX(1U);
    GpioD->PDDR |= (1 << pinD_16);
}

void setup_gpio1()
{
    PortC->PCR[pinC_13] |= PORT_PCR_MUX(1U) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK ;
    GpioD->PDDR |= (0 << pinC_12);
}

void setup_gpio2()
{
    PortC->PCR[pinC_12] |= PORT_PCR_MUX(1U) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK ;
    GpioD->PDDR |= (0 << pinC_12);
}

void delay (uint32_t a)
{
    while(a--);
}

void configInterupt_button1()
{
    PortC->PCR[pinC_12] |= PORT_PCR_ISF_MASK;
    // PortC->PCR[pinC_12] &= ~PORT_PCR_ISF_MASK;
    PortC->PCR[pinC_12] |= PORT_PCR_IRQC(0xA);
 }

void configInterupt_button2()
{
    PortC->PCR[pinC_13] |= PORT_PCR_ISF_MASK;
    // PortC->PCR[pinC_13] &= ~PORT_PCR_ISF_MASK;
    PortC->PCR[pinC_12] |= PORT_PCR_IRQC(0xA);
 }


 void PortC_IRQhandler(void)
 {
    // ISFR: interupt status flag register, mỗi bit tương ứng với 1 pin của PortC
    if(PortC->PCR[12] &  (1 << 12))
    {
        PortC->PCR[12] |= PORT_PCR_ISF_MASK;
        GpioD->PTOR |= (1 << 15);
    }

    if(PortC->PCR[13] &  (1 << 13))
    {
        PortC->PCR[13] |= PORT_PCR_ISF_MASK;
        GpioD->PTOR |= (1 << 16);
    }
 }

 int main()
 {
	 NVIC_SetPriority(PORTC_IRQn,2u);
	 NVIC_EnableIRQ(PORTC_IRQn);
      configInterupt_button1();
      configInterupt_button2();
      setup_gpio1();
      setup_gpio2();
      setup_ledgreen();
      setup_ledred();
      for(;;);

 }
