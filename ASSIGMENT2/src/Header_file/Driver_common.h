/**
 * @file Diver_common.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-10-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef DRIVER_COMMON_H
#define DRIVER_COMMON_H


#include <stdint.h>

/*Operation succeeded.*/
#define 	ARM_DRIVER_OK   0
/*Unspecified error.*/
#define 	ARM_DRIVER_ERROR   -1
/*Driver is busy.*/
#define 	ARM_DRIVER_ERROR_BUSY   -2
/*Timeout occurred.*/
#define 	ARM_DRIVER_ERROR_TIMEOUT   -3
/*Operation not supported.*/
#define 	ARM_DRIVER_ERROR_UNSUPPORTED   -4
/*Parameter error.*/
#define 	ARM_DRIVER_ERROR_PARAMETER   -5
/* 	Start of driver specific errors.*/
#define 	ARM_DRIVER_ERROR_SPECIFIC   -6


typedef struct ARM_DRIVER_VERSION
{
    /*	API version.*/
    uint16_t api;
    /*Driver version. */
    uint16_t drv;
} ARM_DRIVER_VERSION;



typedef enum ARM_POWER_STATE
{
    /*Power off, no operation possible */
    ARM_POWER_OFF = 0,
    /*low power: retain state, detect and signal event*/
    ARM_POWER_LOW,
    /*Power on: full operation at maximum performance.*/
    ARM_POWER_HIGH
}ARM_POWER_STATE;



#endif
