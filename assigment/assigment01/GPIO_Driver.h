/**
 * @file GPIO_Driver.h
 * @author vuong (nguyendinhminhvuong@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdint.h>
#include"S32k144.h"
// #include <S32K144.h>
 #ifndef GPIO_DRIVER_H
 #define GPIO_DRIVER_H
/**
 * @brief to provide API for 
 * 
 */
// #ifdef __cplusplus
// extern "C" {
// #endif

/**
 * @brief set GPIO output or input 
 * 
 */
typedef enum
{
    GPIO_IN = 0u, 
    GPIO_OUT = 1u
}GPIO_set_func;

/**
 * @brief  Pull configuration 
 * 
 */
typedef enum {
    GPIO_NOPULL = 0u,
    GPIO_PULLUP,
    GPIO_PULLDOWN
} Gpio_pull;

/**
 * @brief  interupted configuration 
 * 
 */
typedef enum {
    GPIO_IRQ_DISABLED = 0u,
    GPIO_IRQ_RISING,
    GPIO_IRQ_FALLING,
    GPIO_IRQ_BOTH
} Gpio_irq_mode;

/**
 * @brief GPIO pin descriptor
 * 
 */
typedef struct {
    GPIO_Type *gpio;   /*GPIOA..GPIOE*/ 
    PORT_Type *port;   /*PORTA..PORTE*/ 
    uint8_t    pin;    /*0..31*/ 
} Gpio_pin;

/**
 * @brief callback type
 * 
 */

typedef void (*port_callback)(void); 

 /*******************************
  * API currenly used
  *******************************/
void PORT_EnableClock(PORT_Type *port); /*enable clocking for port*/

void GPIO_Init (const Gpio_pin *port, GPIO_set_func Func, Gpio_pull pull  ); /*set which port and function of its */

void GPIO_Write (const Gpio_pin *port, uint8_t level); 

void GPIO_Toggle(const Gpio_pin *port);

uint8_t GPIO_Read(const Gpio_pin *Port);

/*config interupt and enable callback for APP */
void PORT_ConfigInterrupt(const Gpio_pin *Port, Gpio_irq_mode mode);

void PORT_AttachCallback(PORT_Type *Port, uint8_t pin, port_callback cb);


// void PORT_DetachCallback(PORT_Type *Port, uint8_t pin);

/* LED helpers (active-low) */
static void LED_On(const Gpio_pin *led)
{
	GPIO_Write(led, 0U);
}

static void LED_Off(const Gpio_pin *led)
{
	GPIO_Write(led, 1U);
}




 #endif