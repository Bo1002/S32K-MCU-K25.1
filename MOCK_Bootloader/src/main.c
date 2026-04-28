/******************************************************************************
 * BOOTLOADER MAIN – S32K144
 ******************************************************************************/

#include "S32K144.h"
#include "core_cm4.h"
#include <stdint.h>
#include <stdbool.h>

/* ===== Drivers ===== */
#include "Clock_and_modes.h"
#include "UART_Driver.h"
#include "Flash.h"

/* ===== Queue / Parser ===== */
#include "circle_queue.h"
#include "LineBuild.h"
#include "SrecLineQueue.h"
#include "Parser.h"

/* =========================================================
 * CONFIG
 * ========================================================= */
#define APP_START_ADDR      (0x0000A000UL)
#define APP_SECTOR_COUNT    (16U)

/* ===== BUTTON PC12 ===== */
#define BTN_PORT   IP_PORTC
#define BTN_GPIO   IP_PTC
#define BTN_PIN    13U

/* =========================================================
 * GLOBAL
 * ========================================================= */
extern ARM_DRIVER_USART Driver_USART0;

static ByteQueue_t      g_rxQ;
static LineBuilder_t   g_lineBuilder;
static SrecLineQueue_t g_lineQ;

static volatile bool g_eraseDone  = false;
static volatile bool g_updateDone = false;

static uint8_t  g_rxByte;
static volatile bool uart_tx_done = true;

/* =========================================================
 * SEMIHOSTING OFF
 * ========================================================= */
int _write(int fd, char *ptr, int len) { return len; }
int _read (int fd, char *ptr, int len) { return 0;  }

/* =========================================================
 * BUTTON
 * ========================================================= */
static void Button_Init(void)
{
    IP_PCC->PCCn[PCC_PORTC_INDEX] |= PCC_PCCn_CGC_MASK;

    BTN_PORT->PCR[BTN_PIN] =
        PORT_PCR_MUX(1) |
        PORT_PCR_PE_MASK |
        PORT_PCR_PS_MASK;

    BTN_GPIO->PDDR &= ~(1U << BTN_PIN);
}

static bool Button_Pressed(void)
{
    return ((BTN_GPIO->PDIR & (1U << BTN_PIN)) == 0U);
}

/* =========================================================
 * UART
 * ========================================================= */
static uint8_t mystrlen(const char *s)
{
    uint8_t i = 0;
    while (s[i]) i++;
    return i;
}

static void UART_Send(const char *s)
{
    while (!uart_tx_done);
    uart_tx_done = false;
    Driver_USART0.Send(s, mystrlen(s));
}

void UART_Callback(uint32_t event)
{
    if (event & ARM_USART_EVENT_SEND_COMPLETE)
        uart_tx_done = true;

    if (event & ARM_USART_EVENT_RECEIVE_COMPLETE)
    {
        ByteQueue_Push(&g_rxQ, g_rxByte);
        Driver_USART0.Receive(&g_rxByte, 1);
    }
}

static void UART_Init_App(void)
{
    Driver_USART0.Initialize(UART_Callback);
    Driver_USART0.PowerControl(ARM_POWER_HIGH);
    Driver_USART0.Control(ARM_USART_MODE_ASYNCHRONOUS, 9600);
    Driver_USART0.Control(ARM_USART_CONTROL_TX, 1);
    Driver_USART0.Control(ARM_USART_CONTROL_RX, 1);
}

/* =========================================================
 * LINE BUILDER TASK
 * ========================================================= */
static void LineBuilder_Task(void)
{
    uint8_t ch;

    while (ByteQueue_Pop(&g_rxQ, &ch))
    {
        if (LineBuilder_PushChar(&g_lineBuilder, ch))
        {
            SrecLineQueue_Push(&g_lineQ, g_lineBuilder.buf);
            LineBuilder_Reset(&g_lineBuilder);
        }
    }
}

/* =========================================================
 * PARSER + FLASH TASK
 *
 * ========================================================= */
static void Parser_Task(void)
{
    char line[LINE_MAX_LEN];
    BootPhraseStruct rec;

    static uint8_t  buf[8];
    static uint8_t  idx = 0;
    static uint32_t baseAddr = 0;

    if (!SrecLineQueue_Pop(&g_lineQ, line))
        return;

    ParserResult_t res = Srec_ParseLine(line, &rec);

    if (res == PARSER_OK && rec.Valid && rec.DataLen > 0)
    {
        for (uint8_t i = 0; i < rec.DataLen; i++)
        {
            if (idx == 0)
            {
                baseAddr = (rec.Address + i) & ~0x7U;
            }

            buf[idx++] = rec.Data[i];

            if (idx == 8)
            {
                __disable_irq();
                Program_LongWord_8B(baseAddr, buf);
                __enable_irq();
                idx = 0;
            }
        }
    }
    else if (res == PARSER_EOF)
    {
        if (idx > 0)
        {
            for (uint8_t i = idx; i < 8; i++)
                buf[i] = 0xFF;

            __disable_irq();
            Program_LongWord_8B(baseAddr, buf);
            __enable_irq();
        }

        UART_Send("FW UPDATE DONE\r\n");
        UART_Send("PRESS RESET TO RUN NEW FW\r\n");
        g_updateDone = true;
    }
}

/* =========================================================
 * JUMP TO APP
 * ========================================================= */
static void JumpToApp(uint32_t addr)
{
    uint32_t sp = *(uint32_t *)addr;
    uint32_t pc = *(uint32_t *)(addr + 4U);

    if (sp < 0x1FFF0000UL || sp > 0x20030000UL)
    {
        UART_Send("APP INVALID\r\n");
        while (1);
    }

    __disable_irq();

    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;

    for (uint32_t i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ICPR[i] = 0xFFFFFFFF;
    }

    SCB->VTOR = addr;
    __set_MSP(sp);

    ((void (*)(void))pc)();

    while (1);
}

/* =========================================================
 * MAIN
 * ========================================================= */
int main(void)
{
    bool enterBoot;

    /* CLOCK */
    SOSC_init_8MHz();
    SPLL_init_160MHz();
    NormalRUNmode_80MHz();

    UART_Init_App();
    Button_Init();

    for (volatile uint32_t i = 0; i < 800000; i++);

    enterBoot = Button_Pressed();

    if (!enterBoot)
    {
        JumpToApp(APP_START_ADDR);
    }

    ByteQueue_Init(&g_rxQ);
    LineBuilder_Reset(&g_lineBuilder);
    SrecLineQueue_Init(&g_lineQ);

    Mem_43_INFLS_IPW_LoadAc();

    UART_Send("BOOTLOADER_READY\r\n");
    UART_Send("PRESS BUTTON TO ERASE\r\n");

    Driver_USART0.Receive(&g_rxByte, 1);

    while (1)
    {
        if (!g_eraseDone && Button_Pressed())
        {
            UART_Send("ERASING APP...\r\n");
            while (!uart_tx_done);

            __disable_irq();
            Erase_Multi_Sector(APP_START_ADDR, APP_SECTOR_COUNT);
            __enable_irq();

            g_eraseDone = true;
            UART_Send("ERASE DONE\r\n");
            UART_Send("SEND SREC FILE\r\n");
        }

        if (!g_updateDone)
        {
            LineBuilder_Task();
            Parser_Task();
        }
    }
}
