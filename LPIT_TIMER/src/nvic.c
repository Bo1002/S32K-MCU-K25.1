#include "nvic.h"
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    /*<! Interrupt set enable registers */
    IP_NVIC->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * @brief  Sets the priority of an interrupt or exception with configurable priority level to 1.
 *
 * @param IRQn
 * @param priority
 */
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    IP_NVIC->IP[IRQn]   |= priority;
}

/**
 * @brief <! Clears the pending status of interrupt or exception to 0
 *
 */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    IP_NVIC->ICPR[(uint32_t)(IRQn) >> 5U] = (uint32_t)(1U << ((uint32_t)(IRQn) & (uint32_t)0x1FU));
}
