/*
 * ADC.h
 *
 *  Created on: May 7, 2026
 *      Author: BO
 */

#ifndef ADC_DRIVER_ADC_H_
#define ADC_DRIVER_ADC_H_
#include <stdint.h>

typedef void (*ARM_ADC_SignalEvent_t) (uint32_t event);

typedef struct
{
    int32_t (*intialized)(ARM_ADC_SignalEvent_t cb);
    int32_t (*Readadc) (uint8_t channel);
}ADC_SIG;


#endif /* ADC_DRIVER_ADC_H_ */
