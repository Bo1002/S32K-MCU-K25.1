#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>

/* Base address của NVIC trong Cortex-M4 */
#define SCS_BASE            (0xE000E000UL)            /*!< System Control Space Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)    /*!< NVIC Base Address */
#define NVIC                ((NVIC_Type *) NVIC_BASE) /*!< NVIC configuration struct */

/* Kiểu dữ liệu định nghĩa các thanh ghi NVIC */
typedef struct
{
  volatile uint32_t ISER[8];               /*!< Interrupt Set Enable Register */
           uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];               /*!< Interrupt Clear Enable Register */
           uint32_t RESERVED1[24];
  volatile uint32_t ISPR[8];               /*!< Interrupt Set Pending Register */
           uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];               /*!< Interrupt Clear Pending Register */
           uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];               /*!< Interrupt Active bit Register */
           uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];               /*!< Interrupt Priority Register (8-bit wide) */
           uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                 /*!< Software Trigger Interrupt Register */
} NVIC_Type;

/* ========== API NVIC đơn giản ========== */

/* Enable một IRQ */
static inline void NVIC_EnableIRQ(uint32_t IRQn)
{
    NVIC->ISER[IRQn >> 5U] = (uint32_t)(1UL << (IRQn & 0x1FU));
}

/* Disable một IRQ */
static inline void NVIC_DisableIRQ(uint32_t IRQn)
{
    NVIC->ICER[IRQn >> 5U] = (uint32_t)(1UL << (IRQn & 0x1FU));
}

/* Set Priority cho IRQ */
static inline void NVIC_SetPriority(uint32_t IRQn, uint32_t priority)
{
    NVIC->IP[IRQn] = (uint8_t)((priority & 0xFFU));
}

/* Get Priority */
static inline uint32_t NVIC_GetPriority(uint32_t IRQn)
{
    return ((uint32_t)NVIC->IP[IRQn]);
}

/* Set Pending */
static inline void NVIC_SetPendingIRQ(uint32_t IRQn)
{
    NVIC->ISPR[IRQn >> 5U] = (uint32_t)(1UL << (IRQn & 0x1FU));
}

/* Clear Pending */
static inline void NVIC_ClearPendingIRQ(uint32_t IRQn)
{
    NVIC->ICPR[IRQn >> 5U] = (uint32_t)(1UL << (IRQn & 0x1FU));
}

#endif /* NVIC_H_ */
