#include "S32K144.h"
#include "GPIO_Driver.h"
#include "NVIC.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* LED pins */
static const Gpio_pin g_ledRed   =
{
    .gpio = IP_PTD,
    .port = IP_PORTD,
    .pin = 15U
};
static const Gpio_pin g_ledGreen =
{
    .gpio = IP_PTD,
    .port = IP_PORTD,
    .pin = 16U
};

/* Button pins */
static const Gpio_pin g_btn1 =
{
    .gpio = IP_PTC ,
    .port = IP_PORTC,
    .pin = 12U
};
static const Gpio_pin g_btn2 =
{
    .gpio = IP_PTC ,
    .port = IP_PORTC,
    .pin = 13U
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

static volatile uint8_t s_btn1Event = 0U;
static volatile uint8_t s_btn2Event = 0U;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void Board_Init(void);
static void DelayLoop(volatile uint32_t t);
static void BlinkFast(const Gpio_pin *led, uint8_t times);

static void Btn1_Callback(void);
static void Btn2_Callback(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void Btn1_Callback(void)
{
    s_btn1Event = 1U;
}

static void Btn2_Callback(void)
{
    s_btn2Event = 1U;
}

static void DelayLoop(volatile uint32_t t)
{
    while (t > 0U)
    {
        t--;
    }
}

static void BlinkFast(const Gpio_pin *led, uint8_t times)
{
    uint8_t i;

    for (i = 0U; i < times; i++)
    {
        GPIO_Toggle(led);
        DelayLoop(1000000U);
        GPIO_Toggle(led);
        DelayLoop(1000000U);
    }
}

/* LED helpers (active-low) */
static void LED_On(const Gpio_pin *led)
{
	GPIO_Write(led, 0U);
	DelayLoop(1000000U);
}


static void Board_Init(void)
{
    /* Enable clocks */
    PORT_EnableClock(IP_PORTC);
    PORT_EnableClock(IP_PORTD);

    /* LED init */
    GPIO_Init(&g_ledRed, GPIO_OUT , GPIO_NOPULL);
    GPIO_Init(&g_ledGreen, GPIO_OUT , GPIO_NOPULL);
    LED_On(&g_ledRed);
    LED_On(&g_ledGreen);

    /* Button init */
    GPIO_Init(&g_btn1, GPIO_IN , GPIO_PULLUP);
    GPIO_Init(&g_btn2, GPIO_IN , GPIO_PULLUP);
    PORT_ConfigInterrupt(&g_btn1, GPIO_IRQ_FALLING);
    PORT_ConfigInterrupt(&g_btn2, GPIO_IRQ_FALLING);

    PORT_AttachCallback(g_btn1.port, g_btn1.pin, Btn1_Callback);
    PORT_AttachCallback(g_btn2.port, g_btn2.pin, Btn2_Callback);

    NVIC_SetPriority(PORTC_IRQn, 3U);
    NVIC_ClearPendingIRQ(PORTC_IRQn);
    NVIC_EnableIRQ(PORTC_IRQn);

}
int main(void)
{
    Board_Init();

    while(1)
    {
        if (s_btn1Event != 0U)
        {
            s_btn1Event = 0U;
            BlinkFast(&g_ledRed, 3U);
            LED_On(&g_ledRed);
        }

        if (s_btn2Event != 0U)
        {
            s_btn2Event = 0U;
            BlinkFast(&g_ledGreen, 3U);
            LED_On(&g_ledGreen);
        }

    }

    return 0;
}

