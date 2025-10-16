/**
 * @file UART0_DRIVER.c
 * @brief CMSIS-style driver implementation for LPUART0 on S32K144
 */

#include "S32K144.h"
#include "Header_file/UART_DRIVER.h"
#include "Header_file/Clock_and_modes.h"
#include "Header_file/NVIC.h"

#define UART0_TX_PIN    1U   /* PTB1 - ALT2 (LPUART0_TX) */
#define UART0_RX_PIN    0U   /* PTB0 - ALT2 (LPUART0_RX) */
#define NULL 			0
#define LPUART0_IRQn_ID 31U  /* Interrupt number of LPUART0 (check vector table) */

/* ======================== Driver Private Data ======================== */

static ARM_USART_SignalEvent_t  UART0_cb_event = NULL;
static ARM_USART_STATUS         UART0_Status;
static uint8_t*                 tx_buf;
static uint8_t*                 rx_buf;
static uint32_t                 tx_cnt;
static uint32_t                 rx_cnt;
static uint32_t                 tx_num;
static uint32_t                 rx_num;

/* ======================== Helper Functions ======================== */

static void UART0_PinMux(void)
{
    /* Enable clock for PORTB */
    IP_PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK;

    /* Configure PTB0 and PTB1 as LPUART0 RX/TX */
    IP_PORTB->PCR[UART0_RX_PIN] = PORT_PCR_MUX(2); /* ALT2: LPUART0_RX */
    IP_PORTB->PCR[UART0_TX_PIN] = PORT_PCR_MUX(2); /* ALT2: LPUART0_TX */
}

static void UART0_ClockEnable(void)
{
    /* Enable clock for LPUART0 and select SPLL_DIV2_CLK (80 MHz source /2 = 40 MHz) */
    IP_PCC->PCCn[PCC_LPUART0_INDEX] &= ~PCC_PCCn_CGC_MASK;             /* Disable first */
    IP_PCC->PCCn[PCC_LPUART0_INDEX] |= PCC_PCCn_PCS(6) | PCC_PCCn_CGC_MASK; /* PCS=6 SPLL_DIV2_CLK */
}

/* ======================== API Implementation ======================== */

static ARM_DRIVER_VERSION UART0_GetVersion(void)
{
    ARM_DRIVER_VERSION version = { 2, 0 };
    return version;
}

static ARM_USART_CAPABILITIES UART0_GetCapabilities(void)
{
    ARM_USART_CAPABILITIES cap = {
        .asynchronous = 1,
        .synchronous_master = 0,
        .synchronous_slave = 0,
        .single_wire = 0,
        .irda = 0,
        .smart_card = 0
    };
    return cap;
}

static int32_t UART0_Initialize(ARM_USART_SignalEvent_t cb_event)
{
    UART0_cb_event = cb_event;
    UART0_Status.tx_busy = 0;
    UART0_Status.rx_busy = 0;
    UART0_PinMux();
    UART0_ClockEnable();
    return ARM_DRIVER_OK;
}

static int32_t UART0_Uninitialize(void)
{
    UART0_cb_event = NULL;
    return ARM_DRIVER_OK;
}

static int32_t UART0_PowerControl(ARM_POWER_STATE state)
{
    switch (state)
    {
        case ARM_POWER_OFF:
            IP_PCC->PCCn[PCC_LPUART0_INDEX] &= ~PCC_PCCn_CGC_MASK;
            break;
        case ARM_POWER_LOW:
            /* Not supported */
            return ARM_DRIVER_ERROR_UNSUPPORTED;
        case ARM_POWER_HIGH:
            UART0_ClockEnable();
            break;
    }
    return ARM_DRIVER_OK;
}

static int32_t UART0_Send(const void *data, uint32_t num)
{
    if (UART0_Status.tx_busy) return ARM_DRIVER_ERROR_BUSY;

    tx_buf = (uint8_t *)data;
    tx_cnt = 0;
    tx_num = num;
    UART0_Status.tx_busy = 1;

    IP_LPUART0->CTRL |= LPUART_CTRL_TIE_MASK; /* Enable TX interrupt */
    return ARM_DRIVER_OK;
}

static int32_t UART0_Receive(void *data, uint32_t num)
{
    if (UART0_Status.rx_busy) return ARM_DRIVER_ERROR_BUSY;

    rx_buf = (uint8_t *)data;
    rx_cnt = 0;
    rx_num = num;
    UART0_Status.rx_busy = 1;

    IP_LPUART0->CTRL |= LPUART_CTRL_RIE_MASK; /* Enable RX interrupt */
    return ARM_DRIVER_OK;
}

static int32_t UART0_Control(uint32_t control, uint32_t arg)
{
    switch (control & ARM_USART_CONTROL_Msk)
    {
        case ARM_USART_MODE_ASYNCHRONOUS:
        {
            /* Configure baudrate */
            uint32_t baud = arg;
            uint32_t clk = 40000000U; /* 40 MHz source */
            uint16_t sbr = (uint16_t)(clk / (baud * 16U));
            IP_LPUART0->BAUD = LPUART_BAUD_SBR(sbr);
            IP_LPUART0->CTRL = LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK;
            NVIC_EnableIRQ(LPUART0_IRQn_ID);
            NVIC_SetPriority(LPUART0_IRQn_ID, 2);
            break;
        }

        case ARM_USART_CONTROL_TX:
            if (arg) IP_LPUART0->CTRL |= LPUART_CTRL_TE_MASK;
            else     IP_LPUART0->CTRL &= ~LPUART_CTRL_TE_MASK;
            break;

        case ARM_USART_CONTROL_RX:
            if (arg) IP_LPUART0->CTRL |= LPUART_CTRL_RE_MASK;
            else     IP_LPUART0->CTRL &= ~LPUART_CTRL_RE_MASK;
            break;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
    return ARM_DRIVER_OK;
}

static ARM_USART_STATUS UART0_GetStatus(void)
{
    return UART0_Status;
}

/* ======================== IRQ Handler ======================== */
void LPUART0_IRQHandler(void)
{
    uint32_t status = IP_LPUART0->STAT;

    /* Receive interrupt */
    if ((status & LPUART_STAT_RDRF_MASK) && UART0_Status.rx_busy)
    {
        rx_buf[rx_cnt++] = (uint8_t)IP_LPUART0->DATA;
        if (rx_cnt >= rx_num)
        {
            UART0_Status.rx_busy = 0;
            IP_LPUART0->CTRL &= ~LPUART_CTRL_RIE_MASK;
            if (UART0_cb_event) UART0_cb_event(ARM_USART_EVENT_RECEIVE_COMPLETE);
        }
    }

    /* Transmit interrupt */
    if ((status & LPUART_STAT_TDRE_MASK) && UART0_Status.tx_busy)
    {
        if (tx_cnt < tx_num)
        {
            IP_LPUART0->DATA = tx_buf[tx_cnt++];
        }
        else
        {
            UART0_Status.tx_busy = 0;
            IP_LPUART0->CTRL &= ~LPUART_CTRL_TIE_MASK;
            if (UART0_cb_event) UART0_cb_event(ARM_USART_EVENT_SEND_COMPLETE);
        }
    }
}

/* ======================== Driver Export Structure ======================== */
ARM_DRIVER_USART Driver_USART0 = {
    UART0_GetVersion,
    UART0_GetCapabilities,
    UART0_Initialize,
    UART0_Uninitialize,
    UART0_PowerControl,
    UART0_Send,
    UART0_Receive,
    NULL,
    NULL,
    NULL,
    UART0_Control,
    UART0_GetStatus,
    NULL,
    NULL
};
