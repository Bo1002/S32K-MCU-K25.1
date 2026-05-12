/*
 * common_driver.h
 *
 *  Created on: May 10, 2026
 *      Author: BO
 */

#ifndef CAN_COMMON_DRIVER_H_
#define CAN_COMMON_DRIVER_H_
#include <stdint.h>

/*Satus error code*/
#define     ARM_DRIVER_OK 0
#define     ARM_DRIVER_ERROR -1
#define 	ARM_DRIVER_ERROR_BUSY   -2
#define 	ARM_DRIVER_ERROR_TIMEOUT   -3
#define 	ARM_DRIVER_ERROR_UNSUPPORTED   -4
#define 	ARM_DRIVER_ERROR_PARAMETER   -5
#define 	ARM_DRIVER_ERROR_SPECIFIC   -6

/*ARM_driver get version, use in Getversion function*/
typedef struct 
{
    uint16_t api;
    uint16_t drv;
} ARM_DRIVER_VERSION;

/*relate to power control*/
typedef enum
{
    ARM_POWER_ON,
    ARM_POWER_OFF,
    ARM_POWER_FULL
} ARM_POWER_STATE;

#endif /* CAN_COMMON_DRIVER_H_ */
