#include "Header_file/UART_DRIVER.h"

extern ARM_DRIVER_USART Driver_USART0;
#define NULL 		0
uint8_t rx_buf[64];

int main(void)
{
    SOSC_init_8MHz();
    Driver_USART0.Initialize(NULL);
    Driver_USART0.PowerControl(ARM_POWER_HIGH);
    Driver_USART0.Control(ARM_USART_MODE_ASYNCHRONOUS, 9600);
    char *msg = "Bowcute";
    Driver_USART0.Send(msg,(strlen(msg)));
    Driver_USART0.Receive(rx_buf, sizeof(rx_buf));

    while (1)
    {

    }
}
