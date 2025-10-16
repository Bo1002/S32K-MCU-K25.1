#include "Header_file/UART_DRIVER.h"

extern ARM_DRIVER_USART Driver_USART0;
#define NULL 			0

int main(void)
{
    SOSC_init_8MHz();
    SPLL_init_160MHz();
    NormalRUNmode_80MHz();

    Driver_USART0.Initialize(NULL);
    Driver_USART0.PowerControl(ARM_POWER_HIGH);
    Driver_USART0.Control(ARM_USART_MODE_ASYNCHRONOUS, 115200);

    const char msg[] = "Devlinux provjp!\r\n";
    Driver_USART0.Send(msg, sizeof(msg) - 1);

    while (1) { }
}

