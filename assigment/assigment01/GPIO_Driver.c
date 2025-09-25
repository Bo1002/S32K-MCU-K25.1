/*
 * GPIO_DRIVER.c
 *
 *  Created on: Sep 21, 2025
 *      Author: BO
 */

#include "GPIO_DRIVER.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define Max_pin 32u

/*******************************************************************************
 * prototype
 ******************************************************************************/
static uint32_t Index_from_port (PORT_Type *port);
static uint32_t IRQC_encode(Gpio_irq_mode mode );

/* Callback tables for each port */
static port_callback s_portaCb[Max_pin] = {0};/* callback for port a */

static port_callback s_portbCb[Max_pin] = {0};/* callback for port b*/

static port_callback s_portcCb[Max_pin] = {0};/* callback for port c*/

static port_callback s_portdCb[Max_pin] = {0}; /* callback for port d*/

static port_callback s_porteCb[Max_pin] = {0};/* callback for port e*/



/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t Index_from_port(PORT_Type *port)
{
	uint32_t  index = 0u;
	switch ((uint32_t)port)
	{
	case (uint32_t)IP_PORTA :
		index = PCC_PORTA_INDEX;
		break;

	case (uint32_t)IP_PORTB:
		index = PCC_PORTB_INDEX;
		break;

	case (uint32_t)IP_PORTC:   /*line 10603*/
		index = PCC_PORTC_INDEX;
		break;

	case (uint32_t)IP_PORTD:
		index = PCC_PORTD_INDEX;
		break;

	case (uint32_t)IP_PORTE:
		index = PCC_PORTE_INDEX; /*PCC_PORTE_INDEX 10175 */
		break;
	default:
		break;
	}
	return index;
}

/**
 * @brief : to enable clocking port
 *
 * */
void PORT_EnableClock(PORT_Type *port)
{
	uint32_t index = Index_from_port(port);
	if(index)
	{
		IP_PCC->PCCn[index] |= PCC_PCCn_CGC_MASK; /* line 10137 PCC_PCCn_CGC_MASK, PCCn line 10094, IP_PCC line 10104  */
	}
	else
	{
		/*no value */
	}
}


/**
 * @brief : set function for each GPIO
 *
 * @param Port : address of each port
 * @param Func :
 * @param pull : GPIO_PULLUP or PULL DOWN
 */
void GPIO_Init (const Gpio_pin *Port, GPIO_set_func Func, Gpio_pull pull  )
{
	uint32_t pcr = 0u;
	PORT_EnableClock(Port->port);

	pcr |= PORT_PCR_MUX(1u);
	/* PORT_PCR_MUX_MASK = 1 << 8 = 0x10U =  GPIO */

	if(pull == GPIO_PULLUP)
	{
		pcr |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK; /*line 100636*/
	}

	else if (pull == GPIO_PULLDOWN)
	{
		pcr |= PORT_PCR_PE_MASK; /*PS set default pulldown */
	}

	else
	{
	   /* No value */
	}

	Port->port->PCR[Port->pin] = pcr;

    if (Func == GPIO_OUT)
	{
        Port->gpio->PDDR |= (1 << Port->pin);
    }
    else if (Func == GPIO_IN)
    {
        Port->gpio->PDDR &= ~(1 << Port->pin);
    }
    else
    {
        /* invalid number*/
    }
}

/**
 * @brief
 *
 * @param port  ADDRESS Port
 * @param level write 1 for each peripheral
 */
void GPIO_Write (const Gpio_pin *Port, uint8_t level)
{
	if (level != 0u)
	{
      Port->gpio->PSOR = (1UL << Port->pin);
	}
	else
	{
		Port->gpio->PCOR = (1UL << Port->pin);
	}
}

/**
 * @brief set toggle for GPIO
 *
 * @param port :
 */
void GPIO_Toggle(const Gpio_pin *Port)
{
   Port->gpio->PTOR = (1u << Port->pin);
}

/**
 * @brief
 *
 * @param Port
 * @return uint8_t
 */
uint8_t GPIO_Read(const Gpio_pin *Port)
{
	return (uint8_t)((Port->gpio->PDIR >> Port->pin) & 1UL);
}

/**
 * @brief turn enum in driver directly to hardware
 *
 * @param mode
 * @return uint32_t
 */

static uint32_t IRQC_encode(Gpio_irq_mode mode )
{
  uint32_t val = 0U;
  switch (mode)
  {
  case GPIO_IRQ_RISING:
	val = 0x9U;
	break;
  case GPIO_IRQ_FALLING:
    val = 0xAU;
	break;
  case GPIO_IRQ_BOTH:
    val = 0xBU;
	break;

  default:
	break;
  }
  return val;
}

/**
 * @brief clear and setting flag
 *
 * @param Port address PCR
 * @param mode set mode by IRQC_endcode
 */

void PORT_ConfigInterrupt(const Gpio_pin *Port, Gpio_irq_mode mode)
{
     uint32_t reg = 0u ;
    Port->port->PCR[Port->pin] |= PORT_PCR_ISF_MASK ;

	reg = Port->port->PCR[Port->pin] & ~PORT_PCR_ISF_MASK;  /*clear all IRQC currenlty*/

	reg |= PORT_PCR_IRQC(IRQC_encode (mode));

	Port->port->PCR[Port->pin] = reg;
}


void PORT_AttachCallback(PORT_Type *port, uint8_t pin, port_callback cb)
{
    if (pin >= Max_pin)
    {
        return;
    }

    if (port == IP_PORTA)
    {
        s_portaCb[pin] = cb;
    }
    else if (port == IP_PORTB)
    {
        s_portbCb[pin] = cb;
    }
    else if (port == IP_PORTC)
    {
        s_portcCb[pin] = cb;
    }
    else if (port == IP_PORTD)
    {
        s_portdCb[pin] = cb;
    }
    else if (port == IP_PORTE)
    {
        s_porteCb[pin] = cb;
    }
    else
    {
        /* Invalid port */
    }
}


static inline void service_port(PORT_Type *PORTx, port_callback *tbl)
{
    uint32_t flags = PORTx->ISFR;

    if (flags != 0U)
    {
        uint8_t i;

        for (i = 0U; i < Max_pin; i++)
        {
            if ((flags & (1UL << i)) != 0U)
            {
                PORTx->PCR[i] |= PORT_PCR_ISF_MASK; /* Clear flag */
                if (tbl[i] != 0)
                {
                    tbl[i](); /* Call callback */
                }
                else
                {
                    /* No callback registered */
                }
            }
        }
    }
    else
    {
        /* No flag set */
    }
}

void PORTA_IRQHandler(void)
{
	service_port(IP_PORTA, s_portaCb);
}

void PORTB_IRQHandler(void)
{
	service_port(IP_PORTB, s_portbCb);
}

void PORTC_IRQHandler(void)
{
	service_port(IP_PORTC, s_portcCb);
}

void PORTD_IRQHandler(void)
{
	service_port(IP_PORTD, s_portdCb);
}

void PORTE_IRQHandler(void)
{
	service_port(IP_PORTE, s_porteCb);
}
