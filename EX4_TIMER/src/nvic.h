/**
 * @file driver_nvic.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-09-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef DRIVER_HEADER_DRIVER_NVIC_H_
#define DRIVER_HEADER_DRIVER_NVIC_H_

#include "S32K144.h"

#define NVIC_ISER_COUNT                      8u
#define NVIC_ICER_COUNT                      8u
#define NVIC_ISPR_COUNT                      8u
#define NVIC_ICPR_COUNT                      8u
#define NVIC_IABR_COUNT                      8u
#define NVIC_IP_COUNT                        240u

typedef struct {
  __IO uint32_t ISER[NVIC_ISER_COUNT];         /**< Interrupt Set Enable Register n, array offset: 0x0, array step: 0x4 */
  __IO uint32_t ICER[NVIC_ICER_COUNT];         /**< Interrupt Clear Enable Register n, array offset: 0x80, array step: 0x4 */
  __IO uint32_t ISPR[NVIC_ISPR_COUNT];         /**< Interrupt Set Pending Register n, array offset: 0x100, array step: 0x4 */
  __IO uint32_t ICPR[NVIC_ICPR_COUNT];         /**< Interrupt Clear Pending Register n, array offset: 0x180, array step: 0x4 */
  __IO uint32_t IABR[NVIC_IABR_COUNT];         /**< Interrupt Active bit Register n, array offset: 0x200, array step: 0x4 */
  __IO uint8_t IP[NVIC_IP_COUNT];              /**< Interrupt Priority Register n, array offset: 0x300, array step: 0x1 */
  __O  uint32_t STIR;                          /**< Software Trigger Interrupt Register, offset: 0xE00 */
} NVIC_Type, *NVIC_MemMapPtr;

 /** Number of instances of the NVIC module. */
#define NVIC_INSTANCE_COUNT                  (1u)
 /** Peripheral base address */
#define IP_NVIC_BASE                         (0xE000E100u)
 /** NVIC Pointer */
#define IP_NVIC                              ((NVIC_Type *) IP_NVIC_BASE)
 /** Array initialize NVIC module */
#define IP_NVIC_BASE_ADDRS                   { IP_NVIC_BASE }
 /** Array initialize NVIC pointer */
#define IP_NVIC_BASE_PTRS                    { IP_NVIC }
 /** Number of interrupt vector array for NVIC module */
#define IP_NVIC_IRQS_ARR_COUNT                (1u)
 /** Number of interrupt channels for NVIC module */
#define IP_NVIC_IRQS_CH_COUNT                 (1u)
 /** Interrupt vectos of NVIC peripheral type */
#define IP_NVIC_IRQS                         { SWI_IRQn }


/* ISER Bit Fields */
#define  NVIC_ISER_SETENA_MASK                0xFFFFFFFFu
#define  NVIC_ISER_SETENA_SHIFT               0u
#define  NVIC_ISER_SETENA_WIDTH               32u
#define  NVIC_ISER_SETENA(x)                  (((uint32_t)(((uint32_t)(x))<< NVIC_ISER_SETENA_SHIFT))& NVIC_ISER_SETENA_MASK)
/* ICER Bit Fields */
#define  NVIC_ICER_CLRENA_MASK                0xFFFFFFFFu
#define  NVIC_ICER_CLRENA_SHIFT               0u
#define  NVIC_ICER_CLRENA_WIDTH               32u
#define  NVIC_ICER_CLRENA(x)                  (((uint32_t)(((uint32_t)(x))<< NVIC_ICER_CLRENA_SHIFT))& NVIC_ICER_CLRENA_MASK)
/* ISPR Bit Fields */
#define  NVIC_ISPR_SETPEND_MASK               0xFFFFFFFFu
#define  NVIC_ISPR_SETPEND_SHIFT              0u
#define  NVIC_ISPR_SETPEND_WIDTH              32u
#define  NVIC_ISPR_SETPEND(x)                 (((uint32_t)(((uint32_t)(x))<< NVIC_ISPR_SETPEND_SHIFT))& NVIC_ISPR_SETPEND_MASK)
/* ICPR Bit Fields */
#define  NVIC_ICPR_CLRPEND_MASK               0xFFFFFFFFu
#define  NVIC_ICPR_CLRPEND_SHIFT              0u
#define  NVIC_ICPR_CLRPEND_WIDTH              32u
#define  NVIC_ICPR_CLRPEND(x)                 (((uint32_t)(((uint32_t)(x))<< NVIC_ICPR_CLRPEND_SHIFT))& NVIC_ICPR_CLRPEND_MASK)
/* IABR Bit Fields */
#define  NVIC_IABR_ACTIVE_MASK                0xFFFFFFFFu
#define  NVIC_IABR_ACTIVE_SHIFT               0u
#define  NVIC_IABR_ACTIVE_WIDTH               32u
#define  NVIC_IABR_ACTIVE(x)                  (((uint32_t)(((uint32_t)(x))<< NVIC_IABR_ACTIVE_SHIFT))& NVIC_IABR_ACTIVE_MASK)
/* IP Bit Fields */
#define  NVIC_IP_PRI0_MASK                    0xFFu
#define  NVIC_IP_PRI0_SHIFT                   0u
#define  NVIC_IP_PRI0_WIDTH                   8u
#define  NVIC_IP_PRI0(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI0_SHIFT))& NVIC_IP_PRI0_MASK)
#define  NVIC_IP_PRI1_MASK                    0xFFu
#define  NVIC_IP_PRI1_SHIFT                   0u
#define  NVIC_IP_PRI1_WIDTH                   8u
#define  NVIC_IP_PRI1(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI1_SHIFT))& NVIC_IP_PRI1_MASK)
#define  NVIC_IP_PRI2_MASK                    0xFFu
#define  NVIC_IP_PRI2_SHIFT                   0u
#define  NVIC_IP_PRI2_WIDTH                   8u
#define  NVIC_IP_PRI2(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI2_SHIFT))& NVIC_IP_PRI2_MASK)
#define  NVIC_IP_PRI3_MASK                    0xFFu
#define  NVIC_IP_PRI3_SHIFT                   0u
#define  NVIC_IP_PRI3_WIDTH                   8u
#define  NVIC_IP_PRI3(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI3_SHIFT))& NVIC_IP_PRI3_MASK)
#define  NVIC_IP_PRI4_MASK                    0xFFu
#define  NVIC_IP_PRI4_SHIFT                   0u
#define  NVIC_IP_PRI4_WIDTH                   8u
#define  NVIC_IP_PRI4(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI4_SHIFT))& NVIC_IP_PRI4_MASK)
#define  NVIC_IP_PRI5_MASK                    0xFFu
#define  NVIC_IP_PRI5_SHIFT                   0u
#define  NVIC_IP_PRI5_WIDTH                   8u
#define  NVIC_IP_PRI5(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI5_SHIFT))& NVIC_IP_PRI5_MASK)
#define  NVIC_IP_PRI6_MASK                    0xFFu
#define  NVIC_IP_PRI6_SHIFT                   0u
#define  NVIC_IP_PRI6_WIDTH                   8u
#define  NVIC_IP_PRI6(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI6_SHIFT))& NVIC_IP_PRI6_MASK)
#define  NVIC_IP_PRI7_MASK                    0xFFu
#define  NVIC_IP_PRI7_SHIFT                   0u
#define  NVIC_IP_PRI7_WIDTH                   8u
#define  NVIC_IP_PRI7(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI7_SHIFT))& NVIC_IP_PRI7_MASK)
#define  NVIC_IP_PRI8_MASK                    0xFFu
#define  NVIC_IP_PRI8_SHIFT                   0u
#define  NVIC_IP_PRI8_WIDTH                   8u
#define  NVIC_IP_PRI8(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI8_SHIFT))& NVIC_IP_PRI8_MASK)
#define  NVIC_IP_PRI9_MASK                    0xFFu
#define  NVIC_IP_PRI9_SHIFT                   0u
#define  NVIC_IP_PRI9_WIDTH                   8u
#define  NVIC_IP_PRI9(x)                      (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI9_SHIFT))& NVIC_IP_PRI9_MASK)
#define  NVIC_IP_PRI10_MASK                   0xFFu
#define  NVIC_IP_PRI10_SHIFT                  0u
#define  NVIC_IP_PRI10_WIDTH                  8u
#define  NVIC_IP_PRI10(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI10_SHIFT))& NVIC_IP_PRI10_MASK)
#define  NVIC_IP_PRI11_MASK                   0xFFu
#define  NVIC_IP_PRI11_SHIFT                  0u
#define  NVIC_IP_PRI11_WIDTH                  8u
#define  NVIC_IP_PRI11(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI11_SHIFT))& NVIC_IP_PRI11_MASK)
#define  NVIC_IP_PRI12_MASK                   0xFFu
#define  NVIC_IP_PRI12_SHIFT                  0u
#define  NVIC_IP_PRI12_WIDTH                  8u
#define  NVIC_IP_PRI12(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI12_SHIFT))& NVIC_IP_PRI12_MASK)
#define  NVIC_IP_PRI13_MASK                   0xFFu
#define  NVIC_IP_PRI13_SHIFT                  0u
#define  NVIC_IP_PRI13_WIDTH                  8u
#define  NVIC_IP_PRI13(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI13_SHIFT))& NVIC_IP_PRI13_MASK)
#define  NVIC_IP_PRI14_MASK                   0xFFu
#define  NVIC_IP_PRI14_SHIFT                  0u
#define  NVIC_IP_PRI14_WIDTH                  8u
#define  NVIC_IP_PRI14(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI14_SHIFT))& NVIC_IP_PRI14_MASK)
#define  NVIC_IP_PRI15_MASK                   0xFFu
#define  NVIC_IP_PRI15_SHIFT                  0u
#define  NVIC_IP_PRI15_WIDTH                  8u
#define  NVIC_IP_PRI15(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI15_SHIFT))& NVIC_IP_PRI15_MASK)
#define  NVIC_IP_PRI16_MASK                   0xFFu
#define  NVIC_IP_PRI16_SHIFT                  0u
#define  NVIC_IP_PRI16_WIDTH                  8u
#define  NVIC_IP_PRI16(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI16_SHIFT))& NVIC_IP_PRI16_MASK)
#define  NVIC_IP_PRI17_MASK                   0xFFu
#define  NVIC_IP_PRI17_SHIFT                  0u
#define  NVIC_IP_PRI17_WIDTH                  8u
#define  NVIC_IP_PRI17(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI17_SHIFT))& NVIC_IP_PRI17_MASK)
#define  NVIC_IP_PRI18_MASK                   0xFFu
#define  NVIC_IP_PRI18_SHIFT                  0u
#define  NVIC_IP_PRI18_WIDTH                  8u
#define  NVIC_IP_PRI18(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI18_SHIFT))& NVIC_IP_PRI18_MASK)
#define  NVIC_IP_PRI19_MASK                   0xFFu
#define  NVIC_IP_PRI19_SHIFT                  0u
#define  NVIC_IP_PRI19_WIDTH                  8u
#define  NVIC_IP_PRI19(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI19_SHIFT))& NVIC_IP_PRI19_MASK)
#define  NVIC_IP_PRI20_MASK                   0xFFu
#define  NVIC_IP_PRI20_SHIFT                  0u
#define  NVIC_IP_PRI20_WIDTH                  8u
#define  NVIC_IP_PRI20(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI20_SHIFT))& NVIC_IP_PRI20_MASK)
#define  NVIC_IP_PRI21_MASK                   0xFFu
#define  NVIC_IP_PRI21_SHIFT                  0u
#define  NVIC_IP_PRI21_WIDTH                  8u
#define  NVIC_IP_PRI21(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI21_SHIFT))& NVIC_IP_PRI21_MASK)
#define  NVIC_IP_PRI22_MASK                   0xFFu
#define  NVIC_IP_PRI22_SHIFT                  0u
#define  NVIC_IP_PRI22_WIDTH                  8u
#define  NVIC_IP_PRI22(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI22_SHIFT))& NVIC_IP_PRI22_MASK)
#define  NVIC_IP_PRI23_MASK                   0xFFu
#define  NVIC_IP_PRI23_SHIFT                  0u
#define  NVIC_IP_PRI23_WIDTH                  8u
#define  NVIC_IP_PRI23(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI23_SHIFT))& NVIC_IP_PRI23_MASK)
#define  NVIC_IP_PRI24_MASK                   0xFFu
#define  NVIC_IP_PRI24_SHIFT                  0u
#define  NVIC_IP_PRI24_WIDTH                  8u
#define  NVIC_IP_PRI24(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI24_SHIFT))& NVIC_IP_PRI24_MASK)
#define  NVIC_IP_PRI25_MASK                   0xFFu
#define  NVIC_IP_PRI25_SHIFT                  0u
#define  NVIC_IP_PRI25_WIDTH                  8u
#define  NVIC_IP_PRI25(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI25_SHIFT))& NVIC_IP_PRI25_MASK)
#define  NVIC_IP_PRI26_MASK                   0xFFu
#define  NVIC_IP_PRI26_SHIFT                  0u
#define  NVIC_IP_PRI26_WIDTH                  8u
#define  NVIC_IP_PRI26(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI26_SHIFT))& NVIC_IP_PRI26_MASK)
#define  NVIC_IP_PRI27_MASK                   0xFFu
#define  NVIC_IP_PRI27_SHIFT                  0u
#define  NVIC_IP_PRI27_WIDTH                  8u
#define  NVIC_IP_PRI27(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI27_SHIFT))& NVIC_IP_PRI27_MASK)
#define  NVIC_IP_PRI28_MASK                   0xFFu
#define  NVIC_IP_PRI28_SHIFT                  0u
#define  NVIC_IP_PRI28_WIDTH                  8u
#define  NVIC_IP_PRI28(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI28_SHIFT))& NVIC_IP_PRI28_MASK)
#define  NVIC_IP_PRI29_MASK                   0xFFu
#define  NVIC_IP_PRI29_SHIFT                  0u
#define  NVIC_IP_PRI29_WIDTH                  8u
#define  NVIC_IP_PRI29(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI29_SHIFT))& NVIC_IP_PRI29_MASK)
#define  NVIC_IP_PRI30_MASK                   0xFFu
#define  NVIC_IP_PRI30_SHIFT                  0u
#define  NVIC_IP_PRI30_WIDTH                  8u
#define  NVIC_IP_PRI30(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI30_SHIFT))& NVIC_IP_PRI30_MASK)
#define  NVIC_IP_PRI31_MASK                   0xFFu
#define  NVIC_IP_PRI31_SHIFT                  0u
#define  NVIC_IP_PRI31_WIDTH                  8u
#define  NVIC_IP_PRI31(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI31_SHIFT))& NVIC_IP_PRI31_MASK)
#define  NVIC_IP_PRI32_MASK                   0xFFu
#define  NVIC_IP_PRI32_SHIFT                  0u
#define  NVIC_IP_PRI32_WIDTH                  8u
#define  NVIC_IP_PRI32(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI32_SHIFT))& NVIC_IP_PRI32_MASK)
#define  NVIC_IP_PRI33_MASK                   0xFFu
#define  NVIC_IP_PRI33_SHIFT                  0u
#define  NVIC_IP_PRI33_WIDTH                  8u
#define  NVIC_IP_PRI33(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI33_SHIFT))& NVIC_IP_PRI33_MASK)
#define  NVIC_IP_PRI34_MASK                   0xFFu
#define  NVIC_IP_PRI34_SHIFT                  0u
#define  NVIC_IP_PRI34_WIDTH                  8u
#define  NVIC_IP_PRI34(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI34_SHIFT))& NVIC_IP_PRI34_MASK)
#define  NVIC_IP_PRI35_MASK                   0xFFu
#define  NVIC_IP_PRI35_SHIFT                  0u
#define  NVIC_IP_PRI35_WIDTH                  8u
#define  NVIC_IP_PRI35(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI35_SHIFT))& NVIC_IP_PRI35_MASK)
#define  NVIC_IP_PRI36_MASK                   0xFFu
#define  NVIC_IP_PRI36_SHIFT                  0u
#define  NVIC_IP_PRI36_WIDTH                  8u
#define  NVIC_IP_PRI36(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI36_SHIFT))& NVIC_IP_PRI36_MASK)
#define  NVIC_IP_PRI37_MASK                   0xFFu
#define  NVIC_IP_PRI37_SHIFT                  0u
#define  NVIC_IP_PRI37_WIDTH                  8u
#define  NVIC_IP_PRI37(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI37_SHIFT))& NVIC_IP_PRI37_MASK)
#define  NVIC_IP_PRI38_MASK                   0xFFu
#define  NVIC_IP_PRI38_SHIFT                  0u
#define  NVIC_IP_PRI38_WIDTH                  8u
#define  NVIC_IP_PRI38(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI38_SHIFT))& NVIC_IP_PRI38_MASK)
#define  NVIC_IP_PRI39_MASK                   0xFFu
#define  NVIC_IP_PRI39_SHIFT                  0u
#define  NVIC_IP_PRI39_WIDTH                  8u
#define  NVIC_IP_PRI39(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI39_SHIFT))& NVIC_IP_PRI39_MASK)
#define  NVIC_IP_PRI40_MASK                   0xFFu
#define  NVIC_IP_PRI40_SHIFT                  0u
#define  NVIC_IP_PRI40_WIDTH                  8u
#define  NVIC_IP_PRI40(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI40_SHIFT))& NVIC_IP_PRI40_MASK)
#define  NVIC_IP_PRI41_MASK                   0xFFu
#define  NVIC_IP_PRI41_SHIFT                  0u
#define  NVIC_IP_PRI41_WIDTH                  8u
#define  NVIC_IP_PRI41(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI41_SHIFT))& NVIC_IP_PRI41_MASK)
#define  NVIC_IP_PRI42_MASK                   0xFFu
#define  NVIC_IP_PRI42_SHIFT                  0u
#define  NVIC_IP_PRI42_WIDTH                  8u
#define  NVIC_IP_PRI42(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI42_SHIFT))& NVIC_IP_PRI42_MASK)
#define  NVIC_IP_PRI43_MASK                   0xFFu
#define  NVIC_IP_PRI43_SHIFT                  0u
#define  NVIC_IP_PRI43_WIDTH                  8u
#define  NVIC_IP_PRI43(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI43_SHIFT))& NVIC_IP_PRI43_MASK)
#define  NVIC_IP_PRI44_MASK                   0xFFu
#define  NVIC_IP_PRI44_SHIFT                  0u
#define  NVIC_IP_PRI44_WIDTH                  8u
#define  NVIC_IP_PRI44(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI44_SHIFT))& NVIC_IP_PRI44_MASK)
#define  NVIC_IP_PRI45_MASK                   0xFFu
#define  NVIC_IP_PRI45_SHIFT                  0u
#define  NVIC_IP_PRI45_WIDTH                  8u
#define  NVIC_IP_PRI45(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI45_SHIFT))& NVIC_IP_PRI45_MASK)
#define  NVIC_IP_PRI46_MASK                   0xFFu
#define  NVIC_IP_PRI46_SHIFT                  0u
#define  NVIC_IP_PRI46_WIDTH                  8u
#define  NVIC_IP_PRI46(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI46_SHIFT))& NVIC_IP_PRI46_MASK)
#define  NVIC_IP_PRI47_MASK                   0xFFu
#define  NVIC_IP_PRI47_SHIFT                  0u
#define  NVIC_IP_PRI47_WIDTH                  8u
#define  NVIC_IP_PRI47(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI47_SHIFT))& NVIC_IP_PRI47_MASK)
#define  NVIC_IP_PRI48_MASK                   0xFFu
#define  NVIC_IP_PRI48_SHIFT                  0u
#define  NVIC_IP_PRI48_WIDTH                  8u
#define  NVIC_IP_PRI48(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI48_SHIFT))& NVIC_IP_PRI48_MASK)
#define  NVIC_IP_PRI49_MASK                   0xFFu
#define  NVIC_IP_PRI49_SHIFT                  0u
#define  NVIC_IP_PRI49_WIDTH                  8u
#define  NVIC_IP_PRI49(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI49_SHIFT))& NVIC_IP_PRI49_MASK)
#define  NVIC_IP_PRI50_MASK                   0xFFu
#define  NVIC_IP_PRI50_SHIFT                  0u
#define  NVIC_IP_PRI50_WIDTH                  8u
#define  NVIC_IP_PRI50(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI50_SHIFT))& NVIC_IP_PRI50_MASK)
#define  NVIC_IP_PRI51_MASK                   0xFFu
#define  NVIC_IP_PRI51_SHIFT                  0u
#define  NVIC_IP_PRI51_WIDTH                  8u
#define  NVIC_IP_PRI51(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI51_SHIFT))& NVIC_IP_PRI51_MASK)
#define  NVIC_IP_PRI52_MASK                   0xFFu
#define  NVIC_IP_PRI52_SHIFT                  0u
#define  NVIC_IP_PRI52_WIDTH                  8u
#define  NVIC_IP_PRI52(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI52_SHIFT))& NVIC_IP_PRI52_MASK)
#define  NVIC_IP_PRI53_MASK                   0xFFu
#define  NVIC_IP_PRI53_SHIFT                  0u
#define  NVIC_IP_PRI53_WIDTH                  8u
#define  NVIC_IP_PRI53(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI53_SHIFT))& NVIC_IP_PRI53_MASK)
#define  NVIC_IP_PRI54_MASK                   0xFFu
#define  NVIC_IP_PRI54_SHIFT                  0u
#define  NVIC_IP_PRI54_WIDTH                  8u
#define  NVIC_IP_PRI54(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI54_SHIFT))& NVIC_IP_PRI54_MASK)
#define  NVIC_IP_PRI55_MASK                   0xFFu
#define  NVIC_IP_PRI55_SHIFT                  0u
#define  NVIC_IP_PRI55_WIDTH                  8u
#define  NVIC_IP_PRI55(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI55_SHIFT))& NVIC_IP_PRI55_MASK)
#define  NVIC_IP_PRI56_MASK                   0xFFu
#define  NVIC_IP_PRI56_SHIFT                  0u
#define  NVIC_IP_PRI56_WIDTH                  8u
#define  NVIC_IP_PRI56(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI56_SHIFT))& NVIC_IP_PRI56_MASK)
#define  NVIC_IP_PRI57_MASK                   0xFFu
#define  NVIC_IP_PRI57_SHIFT                  0u
#define  NVIC_IP_PRI57_WIDTH                  8u
#define  NVIC_IP_PRI57(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI57_SHIFT))& NVIC_IP_PRI57_MASK)
#define  NVIC_IP_PRI58_MASK                   0xFFu
#define  NVIC_IP_PRI58_SHIFT                  0u
#define  NVIC_IP_PRI58_WIDTH                  8u
#define  NVIC_IP_PRI58(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI58_SHIFT))& NVIC_IP_PRI58_MASK)
#define  NVIC_IP_PRI59_MASK                   0xFFu
#define  NVIC_IP_PRI59_SHIFT                  0u
#define  NVIC_IP_PRI59_WIDTH                  8u
#define  NVIC_IP_PRI59(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI59_SHIFT))& NVIC_IP_PRI59_MASK)
#define  NVIC_IP_PRI60_MASK                   0xFFu
#define  NVIC_IP_PRI60_SHIFT                  0u
#define  NVIC_IP_PRI60_WIDTH                  8u
#define  NVIC_IP_PRI60(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI60_SHIFT))& NVIC_IP_PRI60_MASK)
#define  NVIC_IP_PRI61_MASK                   0xFFu
#define  NVIC_IP_PRI61_SHIFT                  0u
#define  NVIC_IP_PRI61_WIDTH                  8u
#define  NVIC_IP_PRI61(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI61_SHIFT))& NVIC_IP_PRI61_MASK)
#define  NVIC_IP_PRI62_MASK                   0xFFu
#define  NVIC_IP_PRI62_SHIFT                  0u
#define  NVIC_IP_PRI62_WIDTH                  8u
#define  NVIC_IP_PRI62(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI62_SHIFT))& NVIC_IP_PRI62_MASK)
#define  NVIC_IP_PRI63_MASK                   0xFFu
#define  NVIC_IP_PRI63_SHIFT                  0u
#define  NVIC_IP_PRI63_WIDTH                  8u
#define  NVIC_IP_PRI63(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI63_SHIFT))& NVIC_IP_PRI63_MASK)
#define  NVIC_IP_PRI64_MASK                   0xFFu
#define  NVIC_IP_PRI64_SHIFT                  0u
#define  NVIC_IP_PRI64_WIDTH                  8u
#define  NVIC_IP_PRI64(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI64_SHIFT))& NVIC_IP_PRI64_MASK)
#define  NVIC_IP_PRI65_MASK                   0xFFu
#define  NVIC_IP_PRI65_SHIFT                  0u
#define  NVIC_IP_PRI65_WIDTH                  8u
#define  NVIC_IP_PRI65(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI65_SHIFT))& NVIC_IP_PRI65_MASK)
#define  NVIC_IP_PRI66_MASK                   0xFFu
#define  NVIC_IP_PRI66_SHIFT                  0u
#define  NVIC_IP_PRI66_WIDTH                  8u
#define  NVIC_IP_PRI66(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI66_SHIFT))& NVIC_IP_PRI66_MASK)
#define  NVIC_IP_PRI67_MASK                   0xFFu
#define  NVIC_IP_PRI67_SHIFT                  0u
#define  NVIC_IP_PRI67_WIDTH                  8u
#define  NVIC_IP_PRI67(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI67_SHIFT))& NVIC_IP_PRI67_MASK)
#define  NVIC_IP_PRI68_MASK                   0xFFu
#define  NVIC_IP_PRI68_SHIFT                  0u
#define  NVIC_IP_PRI68_WIDTH                  8u
#define  NVIC_IP_PRI68(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI68_SHIFT))& NVIC_IP_PRI68_MASK)
#define  NVIC_IP_PRI69_MASK                   0xFFu
#define  NVIC_IP_PRI69_SHIFT                  0u
#define  NVIC_IP_PRI69_WIDTH                  8u
#define  NVIC_IP_PRI69(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI69_SHIFT))& NVIC_IP_PRI69_MASK)
#define  NVIC_IP_PRI70_MASK                   0xFFu
#define  NVIC_IP_PRI70_SHIFT                  0u
#define  NVIC_IP_PRI70_WIDTH                  8u
#define  NVIC_IP_PRI70(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI70_SHIFT))& NVIC_IP_PRI70_MASK)
#define  NVIC_IP_PRI71_MASK                   0xFFu
#define  NVIC_IP_PRI71_SHIFT                  0u
#define  NVIC_IP_PRI71_WIDTH                  8u
#define  NVIC_IP_PRI71(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI71_SHIFT))& NVIC_IP_PRI71_MASK)
#define  NVIC_IP_PRI72_MASK                   0xFFu
#define  NVIC_IP_PRI72_SHIFT                  0u
#define  NVIC_IP_PRI72_WIDTH                  8u
#define  NVIC_IP_PRI72(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI72_SHIFT))& NVIC_IP_PRI72_MASK)
#define  NVIC_IP_PRI73_MASK                   0xFFu
#define  NVIC_IP_PRI73_SHIFT                  0u
#define  NVIC_IP_PRI73_WIDTH                  8u
#define  NVIC_IP_PRI73(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI73_SHIFT))& NVIC_IP_PRI73_MASK)
#define  NVIC_IP_PRI74_MASK                   0xFFu
#define  NVIC_IP_PRI74_SHIFT                  0u
#define  NVIC_IP_PRI74_WIDTH                  8u
#define  NVIC_IP_PRI74(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI74_SHIFT))& NVIC_IP_PRI74_MASK)
#define  NVIC_IP_PRI75_MASK                   0xFFu
#define  NVIC_IP_PRI75_SHIFT                  0u
#define  NVIC_IP_PRI75_WIDTH                  8u
#define  NVIC_IP_PRI75(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI75_SHIFT))& NVIC_IP_PRI75_MASK)
#define  NVIC_IP_PRI76_MASK                   0xFFu
#define  NVIC_IP_PRI76_SHIFT                  0u
#define  NVIC_IP_PRI76_WIDTH                  8u
#define  NVIC_IP_PRI76(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI76_SHIFT))& NVIC_IP_PRI76_MASK)
#define  NVIC_IP_PRI77_MASK                   0xFFu
#define  NVIC_IP_PRI77_SHIFT                  0u
#define  NVIC_IP_PRI77_WIDTH                  8u
#define  NVIC_IP_PRI77(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI77_SHIFT))& NVIC_IP_PRI77_MASK)
#define  NVIC_IP_PRI78_MASK                   0xFFu
#define  NVIC_IP_PRI78_SHIFT                  0u
#define  NVIC_IP_PRI78_WIDTH                  8u
#define  NVIC_IP_PRI78(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI78_SHIFT))& NVIC_IP_PRI78_MASK)
#define  NVIC_IP_PRI79_MASK                   0xFFu
#define  NVIC_IP_PRI79_SHIFT                  0u
#define  NVIC_IP_PRI79_WIDTH                  8u
#define  NVIC_IP_PRI79(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI79_SHIFT))& NVIC_IP_PRI79_MASK)
#define  NVIC_IP_PRI80_MASK                   0xFFu
#define  NVIC_IP_PRI80_SHIFT                  0u
#define  NVIC_IP_PRI80_WIDTH                  8u
#define  NVIC_IP_PRI80(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI80_SHIFT))& NVIC_IP_PRI80_MASK)
#define  NVIC_IP_PRI81_MASK                   0xFFu
#define  NVIC_IP_PRI81_SHIFT                  0u
#define  NVIC_IP_PRI81_WIDTH                  8u
#define  NVIC_IP_PRI81(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI81_SHIFT))& NVIC_IP_PRI81_MASK)
#define  NVIC_IP_PRI82_MASK                   0xFFu
#define  NVIC_IP_PRI82_SHIFT                  0u
#define  NVIC_IP_PRI82_WIDTH                  8u
#define  NVIC_IP_PRI82(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI82_SHIFT))& NVIC_IP_PRI82_MASK)
#define  NVIC_IP_PRI83_MASK                   0xFFu
#define  NVIC_IP_PRI83_SHIFT                  0u
#define  NVIC_IP_PRI83_WIDTH                  8u
#define  NVIC_IP_PRI83(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI83_SHIFT))& NVIC_IP_PRI83_MASK)
#define  NVIC_IP_PRI84_MASK                   0xFFu
#define  NVIC_IP_PRI84_SHIFT                  0u
#define  NVIC_IP_PRI84_WIDTH                  8u
#define  NVIC_IP_PRI84(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI84_SHIFT))& NVIC_IP_PRI84_MASK)
#define  NVIC_IP_PRI85_MASK                   0xFFu
#define  NVIC_IP_PRI85_SHIFT                  0u
#define  NVIC_IP_PRI85_WIDTH                  8u
#define  NVIC_IP_PRI85(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI85_SHIFT))& NVIC_IP_PRI85_MASK)
#define  NVIC_IP_PRI86_MASK                   0xFFu
#define  NVIC_IP_PRI86_SHIFT                  0u
#define  NVIC_IP_PRI86_WIDTH                  8u
#define  NVIC_IP_PRI86(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI86_SHIFT))& NVIC_IP_PRI86_MASK)
#define  NVIC_IP_PRI87_MASK                   0xFFu
#define  NVIC_IP_PRI87_SHIFT                  0u
#define  NVIC_IP_PRI87_WIDTH                  8u
#define  NVIC_IP_PRI87(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI87_SHIFT))& NVIC_IP_PRI87_MASK)
#define  NVIC_IP_PRI88_MASK                   0xFFu
#define  NVIC_IP_PRI88_SHIFT                  0u
#define  NVIC_IP_PRI88_WIDTH                  8u
#define  NVIC_IP_PRI88(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI88_SHIFT))& NVIC_IP_PRI88_MASK)
#define  NVIC_IP_PRI89_MASK                   0xFFu
#define  NVIC_IP_PRI89_SHIFT                  0u
#define  NVIC_IP_PRI89_WIDTH                  8u
#define  NVIC_IP_PRI89(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI89_SHIFT))& NVIC_IP_PRI89_MASK)
#define  NVIC_IP_PRI90_MASK                   0xFFu
#define  NVIC_IP_PRI90_SHIFT                  0u
#define  NVIC_IP_PRI90_WIDTH                  8u
#define  NVIC_IP_PRI90(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI90_SHIFT))& NVIC_IP_PRI90_MASK)
#define  NVIC_IP_PRI91_MASK                   0xFFu
#define  NVIC_IP_PRI91_SHIFT                  0u
#define  NVIC_IP_PRI91_WIDTH                  8u
#define  NVIC_IP_PRI91(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI91_SHIFT))& NVIC_IP_PRI91_MASK)
#define  NVIC_IP_PRI92_MASK                   0xFFu
#define  NVIC_IP_PRI92_SHIFT                  0u
#define  NVIC_IP_PRI92_WIDTH                  8u
#define  NVIC_IP_PRI92(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI92_SHIFT))& NVIC_IP_PRI92_MASK)
#define  NVIC_IP_PRI93_MASK                   0xFFu
#define  NVIC_IP_PRI93_SHIFT                  0u
#define  NVIC_IP_PRI93_WIDTH                  8u
#define  NVIC_IP_PRI93(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI93_SHIFT))& NVIC_IP_PRI93_MASK)
#define  NVIC_IP_PRI94_MASK                   0xFFu
#define  NVIC_IP_PRI94_SHIFT                  0u
#define  NVIC_IP_PRI94_WIDTH                  8u
#define  NVIC_IP_PRI94(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI94_SHIFT))& NVIC_IP_PRI94_MASK)
#define  NVIC_IP_PRI95_MASK                   0xFFu
#define  NVIC_IP_PRI95_SHIFT                  0u
#define  NVIC_IP_PRI95_WIDTH                  8u
#define  NVIC_IP_PRI95(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI95_SHIFT))& NVIC_IP_PRI95_MASK)
#define  NVIC_IP_PRI96_MASK                   0xFFu
#define  NVIC_IP_PRI96_SHIFT                  0u
#define  NVIC_IP_PRI96_WIDTH                  8u
#define  NVIC_IP_PRI96(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI96_SHIFT))& NVIC_IP_PRI96_MASK)
#define  NVIC_IP_PRI97_MASK                   0xFFu
#define  NVIC_IP_PRI97_SHIFT                  0u
#define  NVIC_IP_PRI97_WIDTH                  8u
#define  NVIC_IP_PRI97(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI97_SHIFT))& NVIC_IP_PRI97_MASK)
#define  NVIC_IP_PRI98_MASK                   0xFFu
#define  NVIC_IP_PRI98_SHIFT                  0u
#define  NVIC_IP_PRI98_WIDTH                  8u
#define  NVIC_IP_PRI98(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI98_SHIFT))& NVIC_IP_PRI98_MASK)
#define  NVIC_IP_PRI99_MASK                   0xFFu
#define  NVIC_IP_PRI99_SHIFT                  0u
#define  NVIC_IP_PRI99_WIDTH                  8u
#define  NVIC_IP_PRI99(x)                     (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI99_SHIFT))& NVIC_IP_PRI99_MASK)
#define  NVIC_IP_PRI100_MASK                  0xFFu
#define  NVIC_IP_PRI100_SHIFT                 0u
#define  NVIC_IP_PRI100_WIDTH                 8u
#define  NVIC_IP_PRI100(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI100_SHIFT))& NVIC_IP_PRI100_MASK)
#define  NVIC_IP_PRI101_MASK                  0xFFu
#define  NVIC_IP_PRI101_SHIFT                 0u
#define  NVIC_IP_PRI101_WIDTH                 8u
#define  NVIC_IP_PRI101(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI101_SHIFT))& NVIC_IP_PRI101_MASK)
#define  NVIC_IP_PRI102_MASK                  0xFFu
#define  NVIC_IP_PRI102_SHIFT                 0u
#define  NVIC_IP_PRI102_WIDTH                 8u
#define  NVIC_IP_PRI102(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI102_SHIFT))& NVIC_IP_PRI102_MASK)
#define  NVIC_IP_PRI103_MASK                  0xFFu
#define  NVIC_IP_PRI103_SHIFT                 0u
#define  NVIC_IP_PRI103_WIDTH                 8u
#define  NVIC_IP_PRI103(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI103_SHIFT))& NVIC_IP_PRI103_MASK)
#define  NVIC_IP_PRI104_MASK                  0xFFu
#define  NVIC_IP_PRI104_SHIFT                 0u
#define  NVIC_IP_PRI104_WIDTH                 8u
#define  NVIC_IP_PRI104(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI104_SHIFT))& NVIC_IP_PRI104_MASK)
#define  NVIC_IP_PRI105_MASK                  0xFFu
#define  NVIC_IP_PRI105_SHIFT                 0u
#define  NVIC_IP_PRI105_WIDTH                 8u
#define  NVIC_IP_PRI105(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI105_SHIFT))& NVIC_IP_PRI105_MASK)
#define  NVIC_IP_PRI106_MASK                  0xFFu
#define  NVIC_IP_PRI106_SHIFT                 0u
#define  NVIC_IP_PRI106_WIDTH                 8u
#define  NVIC_IP_PRI106(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI106_SHIFT))& NVIC_IP_PRI106_MASK)
#define  NVIC_IP_PRI107_MASK                  0xFFu
#define  NVIC_IP_PRI107_SHIFT                 0u
#define  NVIC_IP_PRI107_WIDTH                 8u
#define  NVIC_IP_PRI107(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI107_SHIFT))& NVIC_IP_PRI107_MASK)
#define  NVIC_IP_PRI108_MASK                  0xFFu
#define  NVIC_IP_PRI108_SHIFT                 0u
#define  NVIC_IP_PRI108_WIDTH                 8u
#define  NVIC_IP_PRI108(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI108_SHIFT))& NVIC_IP_PRI108_MASK)
#define  NVIC_IP_PRI109_MASK                  0xFFu
#define  NVIC_IP_PRI109_SHIFT                 0u
#define  NVIC_IP_PRI109_WIDTH                 8u
#define  NVIC_IP_PRI109(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI109_SHIFT))& NVIC_IP_PRI109_MASK)
#define  NVIC_IP_PRI110_MASK                  0xFFu
#define  NVIC_IP_PRI110_SHIFT                 0u
#define  NVIC_IP_PRI110_WIDTH                 8u
#define  NVIC_IP_PRI110(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI110_SHIFT))& NVIC_IP_PRI110_MASK)
#define  NVIC_IP_PRI111_MASK                  0xFFu
#define  NVIC_IP_PRI111_SHIFT                 0u
#define  NVIC_IP_PRI111_WIDTH                 8u
#define  NVIC_IP_PRI111(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI111_SHIFT))& NVIC_IP_PRI111_MASK)
#define  NVIC_IP_PRI112_MASK                  0xFFu
#define  NVIC_IP_PRI112_SHIFT                 0u
#define  NVIC_IP_PRI112_WIDTH                 8u
#define  NVIC_IP_PRI112(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI112_SHIFT))& NVIC_IP_PRI112_MASK)
#define  NVIC_IP_PRI113_MASK                  0xFFu
#define  NVIC_IP_PRI113_SHIFT                 0u
#define  NVIC_IP_PRI113_WIDTH                 8u
#define  NVIC_IP_PRI113(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI113_SHIFT))& NVIC_IP_PRI113_MASK)
#define  NVIC_IP_PRI114_MASK                  0xFFu
#define  NVIC_IP_PRI114_SHIFT                 0u
#define  NVIC_IP_PRI114_WIDTH                 8u
#define  NVIC_IP_PRI114(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI114_SHIFT))& NVIC_IP_PRI114_MASK)
#define  NVIC_IP_PRI115_MASK                  0xFFu
#define  NVIC_IP_PRI115_SHIFT                 0u
#define  NVIC_IP_PRI115_WIDTH                 8u
#define  NVIC_IP_PRI115(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI115_SHIFT))& NVIC_IP_PRI115_MASK)
#define  NVIC_IP_PRI116_MASK                  0xFFu
#define  NVIC_IP_PRI116_SHIFT                 0u
#define  NVIC_IP_PRI116_WIDTH                 8u
#define  NVIC_IP_PRI116(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI116_SHIFT))& NVIC_IP_PRI116_MASK)
#define  NVIC_IP_PRI117_MASK                  0xFFu
#define  NVIC_IP_PRI117_SHIFT                 0u
#define  NVIC_IP_PRI117_WIDTH                 8u
#define  NVIC_IP_PRI117(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI117_SHIFT))& NVIC_IP_PRI117_MASK)
#define  NVIC_IP_PRI118_MASK                  0xFFu
#define  NVIC_IP_PRI118_SHIFT                 0u
#define  NVIC_IP_PRI118_WIDTH                 8u
#define  NVIC_IP_PRI118(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI118_SHIFT))& NVIC_IP_PRI118_MASK)
#define  NVIC_IP_PRI119_MASK                  0xFFu
#define  NVIC_IP_PRI119_SHIFT                 0u
#define  NVIC_IP_PRI119_WIDTH                 8u
#define  NVIC_IP_PRI119(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI119_SHIFT))& NVIC_IP_PRI119_MASK)
#define  NVIC_IP_PRI120_MASK                  0xFFu
#define  NVIC_IP_PRI120_SHIFT                 0u
#define  NVIC_IP_PRI120_WIDTH                 8u
#define  NVIC_IP_PRI120(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI120_SHIFT))& NVIC_IP_PRI120_MASK)
#define  NVIC_IP_PRI121_MASK                  0xFFu
#define  NVIC_IP_PRI121_SHIFT                 0u
#define  NVIC_IP_PRI121_WIDTH                 8u
#define  NVIC_IP_PRI121(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI121_SHIFT))& NVIC_IP_PRI121_MASK)
#define  NVIC_IP_PRI122_MASK                  0xFFu
#define  NVIC_IP_PRI122_SHIFT                 0u
#define  NVIC_IP_PRI122_WIDTH                 8u
#define  NVIC_IP_PRI122(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI122_SHIFT))& NVIC_IP_PRI122_MASK)
#define  NVIC_IP_PRI123_MASK                  0xFFu
#define  NVIC_IP_PRI123_SHIFT                 0u
#define  NVIC_IP_PRI123_WIDTH                 8u
#define  NVIC_IP_PRI123(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI123_SHIFT))& NVIC_IP_PRI123_MASK)
#define  NVIC_IP_PRI124_MASK                  0xFFu
#define  NVIC_IP_PRI124_SHIFT                 0u
#define  NVIC_IP_PRI124_WIDTH                 8u
#define  NVIC_IP_PRI124(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI124_SHIFT))& NVIC_IP_PRI124_MASK)
#define  NVIC_IP_PRI125_MASK                  0xFFu
#define  NVIC_IP_PRI125_SHIFT                 0u
#define  NVIC_IP_PRI125_WIDTH                 8u
#define  NVIC_IP_PRI125(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI125_SHIFT))& NVIC_IP_PRI125_MASK)
#define  NVIC_IP_PRI126_MASK                  0xFFu
#define  NVIC_IP_PRI126_SHIFT                 0u
#define  NVIC_IP_PRI126_WIDTH                 8u
#define  NVIC_IP_PRI126(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI126_SHIFT))& NVIC_IP_PRI126_MASK)
#define  NVIC_IP_PRI127_MASK                  0xFFu
#define  NVIC_IP_PRI127_SHIFT                 0u
#define  NVIC_IP_PRI127_WIDTH                 8u
#define  NVIC_IP_PRI127(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI127_SHIFT))& NVIC_IP_PRI127_MASK)
#define  NVIC_IP_PRI128_MASK                  0xFFu
#define  NVIC_IP_PRI128_SHIFT                 0u
#define  NVIC_IP_PRI128_WIDTH                 8u
#define  NVIC_IP_PRI128(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI128_SHIFT))& NVIC_IP_PRI128_MASK)
#define  NVIC_IP_PRI129_MASK                  0xFFu
#define  NVIC_IP_PRI129_SHIFT                 0u
#define  NVIC_IP_PRI129_WIDTH                 8u
#define  NVIC_IP_PRI129(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI129_SHIFT))& NVIC_IP_PRI129_MASK)
#define  NVIC_IP_PRI130_MASK                  0xFFu
#define  NVIC_IP_PRI130_SHIFT                 0u
#define  NVIC_IP_PRI130_WIDTH                 8u
#define  NVIC_IP_PRI130(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI130_SHIFT))& NVIC_IP_PRI130_MASK)
#define  NVIC_IP_PRI131_MASK                  0xFFu
#define  NVIC_IP_PRI131_SHIFT                 0u
#define  NVIC_IP_PRI131_WIDTH                 8u
#define  NVIC_IP_PRI131(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI131_SHIFT))& NVIC_IP_PRI131_MASK)
#define  NVIC_IP_PRI132_MASK                  0xFFu
#define  NVIC_IP_PRI132_SHIFT                 0u
#define  NVIC_IP_PRI132_WIDTH                 8u
#define  NVIC_IP_PRI132(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI132_SHIFT))& NVIC_IP_PRI132_MASK)
#define  NVIC_IP_PRI133_MASK                  0xFFu
#define  NVIC_IP_PRI133_SHIFT                 0u
#define  NVIC_IP_PRI133_WIDTH                 8u
#define  NVIC_IP_PRI133(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI133_SHIFT))& NVIC_IP_PRI133_MASK)
#define  NVIC_IP_PRI134_MASK                  0xFFu
#define  NVIC_IP_PRI134_SHIFT                 0u
#define  NVIC_IP_PRI134_WIDTH                 8u
#define  NVIC_IP_PRI134(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI134_SHIFT))& NVIC_IP_PRI134_MASK)
#define  NVIC_IP_PRI135_MASK                  0xFFu
#define  NVIC_IP_PRI135_SHIFT                 0u
#define  NVIC_IP_PRI135_WIDTH                 8u
#define  NVIC_IP_PRI135(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI135_SHIFT))& NVIC_IP_PRI135_MASK)
#define  NVIC_IP_PRI136_MASK                  0xFFu
#define  NVIC_IP_PRI136_SHIFT                 0u
#define  NVIC_IP_PRI136_WIDTH                 8u
#define  NVIC_IP_PRI136(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI136_SHIFT))& NVIC_IP_PRI136_MASK)
#define  NVIC_IP_PRI137_MASK                  0xFFu
#define  NVIC_IP_PRI137_SHIFT                 0u
#define  NVIC_IP_PRI137_WIDTH                 8u
#define  NVIC_IP_PRI137(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI137_SHIFT))& NVIC_IP_PRI137_MASK)
#define  NVIC_IP_PRI138_MASK                  0xFFu
#define  NVIC_IP_PRI138_SHIFT                 0u
#define  NVIC_IP_PRI138_WIDTH                 8u
#define  NVIC_IP_PRI138(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI138_SHIFT))& NVIC_IP_PRI138_MASK)
#define  NVIC_IP_PRI139_MASK                  0xFFu
#define  NVIC_IP_PRI139_SHIFT                 0u
#define  NVIC_IP_PRI139_WIDTH                 8u
#define  NVIC_IP_PRI139(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI139_SHIFT))& NVIC_IP_PRI139_MASK)
#define  NVIC_IP_PRI140_MASK                  0xFFu
#define  NVIC_IP_PRI140_SHIFT                 0u
#define  NVIC_IP_PRI140_WIDTH                 8u
#define  NVIC_IP_PRI140(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI140_SHIFT))& NVIC_IP_PRI140_MASK)
#define  NVIC_IP_PRI141_MASK                  0xFFu
#define  NVIC_IP_PRI141_SHIFT                 0u
#define  NVIC_IP_PRI141_WIDTH                 8u
#define  NVIC_IP_PRI141(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI141_SHIFT))& NVIC_IP_PRI141_MASK)
#define  NVIC_IP_PRI142_MASK                  0xFFu
#define  NVIC_IP_PRI142_SHIFT                 0u
#define  NVIC_IP_PRI142_WIDTH                 8u
#define  NVIC_IP_PRI142(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI142_SHIFT))& NVIC_IP_PRI142_MASK)
#define  NVIC_IP_PRI143_MASK                  0xFFu
#define  NVIC_IP_PRI143_SHIFT                 0u
#define  NVIC_IP_PRI143_WIDTH                 8u
#define  NVIC_IP_PRI143(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI143_SHIFT))& NVIC_IP_PRI143_MASK)
#define  NVIC_IP_PRI144_MASK                  0xFFu
#define  NVIC_IP_PRI144_SHIFT                 0u
#define  NVIC_IP_PRI144_WIDTH                 8u
#define  NVIC_IP_PRI144(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI144_SHIFT))& NVIC_IP_PRI144_MASK)
#define  NVIC_IP_PRI145_MASK                  0xFFu
#define  NVIC_IP_PRI145_SHIFT                 0u
#define  NVIC_IP_PRI145_WIDTH                 8u
#define  NVIC_IP_PRI145(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI145_SHIFT))& NVIC_IP_PRI145_MASK)
#define  NVIC_IP_PRI146_MASK                  0xFFu
#define  NVIC_IP_PRI146_SHIFT                 0u
#define  NVIC_IP_PRI146_WIDTH                 8u
#define  NVIC_IP_PRI146(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI146_SHIFT))& NVIC_IP_PRI146_MASK)
#define  NVIC_IP_PRI147_MASK                  0xFFu
#define  NVIC_IP_PRI147_SHIFT                 0u
#define  NVIC_IP_PRI147_WIDTH                 8u
#define  NVIC_IP_PRI147(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI147_SHIFT))& NVIC_IP_PRI147_MASK)
#define  NVIC_IP_PRI148_MASK                  0xFFu
#define  NVIC_IP_PRI148_SHIFT                 0u
#define  NVIC_IP_PRI148_WIDTH                 8u
#define  NVIC_IP_PRI148(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI148_SHIFT))& NVIC_IP_PRI148_MASK)
#define  NVIC_IP_PRI149_MASK                  0xFFu
#define  NVIC_IP_PRI149_SHIFT                 0u
#define  NVIC_IP_PRI149_WIDTH                 8u
#define  NVIC_IP_PRI149(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI149_SHIFT))& NVIC_IP_PRI149_MASK)
#define  NVIC_IP_PRI150_MASK                  0xFFu
#define  NVIC_IP_PRI150_SHIFT                 0u
#define  NVIC_IP_PRI150_WIDTH                 8u
#define  NVIC_IP_PRI150(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI150_SHIFT))& NVIC_IP_PRI150_MASK)
#define  NVIC_IP_PRI151_MASK                  0xFFu
#define  NVIC_IP_PRI151_SHIFT                 0u
#define  NVIC_IP_PRI151_WIDTH                 8u
#define  NVIC_IP_PRI151(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI151_SHIFT))& NVIC_IP_PRI151_MASK)
#define  NVIC_IP_PRI152_MASK                  0xFFu
#define  NVIC_IP_PRI152_SHIFT                 0u
#define  NVIC_IP_PRI152_WIDTH                 8u
#define  NVIC_IP_PRI152(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI152_SHIFT))& NVIC_IP_PRI152_MASK)
#define  NVIC_IP_PRI153_MASK                  0xFFu
#define  NVIC_IP_PRI153_SHIFT                 0u
#define  NVIC_IP_PRI153_WIDTH                 8u
#define  NVIC_IP_PRI153(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI153_SHIFT))& NVIC_IP_PRI153_MASK)
#define  NVIC_IP_PRI154_MASK                  0xFFu
#define  NVIC_IP_PRI154_SHIFT                 0u
#define  NVIC_IP_PRI154_WIDTH                 8u
#define  NVIC_IP_PRI154(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI154_SHIFT))& NVIC_IP_PRI154_MASK)
#define  NVIC_IP_PRI155_MASK                  0xFFu
#define  NVIC_IP_PRI155_SHIFT                 0u
#define  NVIC_IP_PRI155_WIDTH                 8u
#define  NVIC_IP_PRI155(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI155_SHIFT))& NVIC_IP_PRI155_MASK)
#define  NVIC_IP_PRI156_MASK                  0xFFu
#define  NVIC_IP_PRI156_SHIFT                 0u
#define  NVIC_IP_PRI156_WIDTH                 8u
#define  NVIC_IP_PRI156(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI156_SHIFT))& NVIC_IP_PRI156_MASK)
#define  NVIC_IP_PRI157_MASK                  0xFFu
#define  NVIC_IP_PRI157_SHIFT                 0u
#define  NVIC_IP_PRI157_WIDTH                 8u
#define  NVIC_IP_PRI157(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI157_SHIFT))& NVIC_IP_PRI157_MASK)
#define  NVIC_IP_PRI158_MASK                  0xFFu
#define  NVIC_IP_PRI158_SHIFT                 0u
#define  NVIC_IP_PRI158_WIDTH                 8u
#define  NVIC_IP_PRI158(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI158_SHIFT))& NVIC_IP_PRI158_MASK)
#define  NVIC_IP_PRI159_MASK                  0xFFu
#define  NVIC_IP_PRI159_SHIFT                 0u
#define  NVIC_IP_PRI159_WIDTH                 8u
#define  NVIC_IP_PRI159(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI159_SHIFT))& NVIC_IP_PRI159_MASK)
#define  NVIC_IP_PRI160_MASK                  0xFFu
#define  NVIC_IP_PRI160_SHIFT                 0u
#define  NVIC_IP_PRI160_WIDTH                 8u
#define  NVIC_IP_PRI160(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI160_SHIFT))& NVIC_IP_PRI160_MASK)
#define  NVIC_IP_PRI161_MASK                  0xFFu
#define  NVIC_IP_PRI161_SHIFT                 0u
#define  NVIC_IP_PRI161_WIDTH                 8u
#define  NVIC_IP_PRI161(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI161_SHIFT))& NVIC_IP_PRI161_MASK)
#define  NVIC_IP_PRI162_MASK                  0xFFu
#define  NVIC_IP_PRI162_SHIFT                 0u
#define  NVIC_IP_PRI162_WIDTH                 8u
#define  NVIC_IP_PRI162(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI162_SHIFT))& NVIC_IP_PRI162_MASK)
#define  NVIC_IP_PRI163_MASK                  0xFFu
#define  NVIC_IP_PRI163_SHIFT                 0u
#define  NVIC_IP_PRI163_WIDTH                 8u
#define  NVIC_IP_PRI163(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI163_SHIFT))& NVIC_IP_PRI163_MASK)
#define  NVIC_IP_PRI164_MASK                  0xFFu
#define  NVIC_IP_PRI164_SHIFT                 0u
#define  NVIC_IP_PRI164_WIDTH                 8u
#define  NVIC_IP_PRI164(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI164_SHIFT))& NVIC_IP_PRI164_MASK)
#define  NVIC_IP_PRI165_MASK                  0xFFu
#define  NVIC_IP_PRI165_SHIFT                 0u
#define  NVIC_IP_PRI165_WIDTH                 8u
#define  NVIC_IP_PRI165(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI165_SHIFT))& NVIC_IP_PRI165_MASK)
#define  NVIC_IP_PRI166_MASK                  0xFFu
#define  NVIC_IP_PRI166_SHIFT                 0u
#define  NVIC_IP_PRI166_WIDTH                 8u
#define  NVIC_IP_PRI166(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI166_SHIFT))& NVIC_IP_PRI166_MASK)
#define  NVIC_IP_PRI167_MASK                  0xFFu
#define  NVIC_IP_PRI167_SHIFT                 0u
#define  NVIC_IP_PRI167_WIDTH                 8u
#define  NVIC_IP_PRI167(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI167_SHIFT))& NVIC_IP_PRI167_MASK)
#define  NVIC_IP_PRI168_MASK                  0xFFu
#define  NVIC_IP_PRI168_SHIFT                 0u
#define  NVIC_IP_PRI168_WIDTH                 8u
#define  NVIC_IP_PRI168(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI168_SHIFT))& NVIC_IP_PRI168_MASK)
#define  NVIC_IP_PRI169_MASK                  0xFFu
#define  NVIC_IP_PRI169_SHIFT                 0u
#define  NVIC_IP_PRI169_WIDTH                 8u
#define  NVIC_IP_PRI169(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI169_SHIFT))& NVIC_IP_PRI169_MASK)
#define  NVIC_IP_PRI170_MASK                  0xFFu
#define  NVIC_IP_PRI170_SHIFT                 0u
#define  NVIC_IP_PRI170_WIDTH                 8u
#define  NVIC_IP_PRI170(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI170_SHIFT))& NVIC_IP_PRI170_MASK)
#define  NVIC_IP_PRI171_MASK                  0xFFu
#define  NVIC_IP_PRI171_SHIFT                 0u
#define  NVIC_IP_PRI171_WIDTH                 8u
#define  NVIC_IP_PRI171(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI171_SHIFT))& NVIC_IP_PRI171_MASK)
#define  NVIC_IP_PRI172_MASK                  0xFFu
#define  NVIC_IP_PRI172_SHIFT                 0u
#define  NVIC_IP_PRI172_WIDTH                 8u
#define  NVIC_IP_PRI172(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI172_SHIFT))& NVIC_IP_PRI172_MASK)
#define  NVIC_IP_PRI173_MASK                  0xFFu
#define  NVIC_IP_PRI173_SHIFT                 0u
#define  NVIC_IP_PRI173_WIDTH                 8u
#define  NVIC_IP_PRI173(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI173_SHIFT))& NVIC_IP_PRI173_MASK)
#define  NVIC_IP_PRI174_MASK                  0xFFu
#define  NVIC_IP_PRI174_SHIFT                 0u
#define  NVIC_IP_PRI174_WIDTH                 8u
#define  NVIC_IP_PRI174(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI174_SHIFT))& NVIC_IP_PRI174_MASK)
#define  NVIC_IP_PRI175_MASK                  0xFFu
#define  NVIC_IP_PRI175_SHIFT                 0u
#define  NVIC_IP_PRI175_WIDTH                 8u
#define  NVIC_IP_PRI175(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI175_SHIFT))& NVIC_IP_PRI175_MASK)
#define  NVIC_IP_PRI176_MASK                  0xFFu
#define  NVIC_IP_PRI176_SHIFT                 0u
#define  NVIC_IP_PRI176_WIDTH                 8u
#define  NVIC_IP_PRI176(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI176_SHIFT))& NVIC_IP_PRI176_MASK)
#define  NVIC_IP_PRI177_MASK                  0xFFu
#define  NVIC_IP_PRI177_SHIFT                 0u
#define  NVIC_IP_PRI177_WIDTH                 8u
#define  NVIC_IP_PRI177(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI177_SHIFT))& NVIC_IP_PRI177_MASK)
#define  NVIC_IP_PRI178_MASK                  0xFFu
#define  NVIC_IP_PRI178_SHIFT                 0u
#define  NVIC_IP_PRI178_WIDTH                 8u
#define  NVIC_IP_PRI178(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI178_SHIFT))& NVIC_IP_PRI178_MASK)
#define  NVIC_IP_PRI179_MASK                  0xFFu
#define  NVIC_IP_PRI179_SHIFT                 0u
#define  NVIC_IP_PRI179_WIDTH                 8u
#define  NVIC_IP_PRI179(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI179_SHIFT))& NVIC_IP_PRI179_MASK)
#define  NVIC_IP_PRI180_MASK                  0xFFu
#define  NVIC_IP_PRI180_SHIFT                 0u
#define  NVIC_IP_PRI180_WIDTH                 8u
#define  NVIC_IP_PRI180(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI180_SHIFT))& NVIC_IP_PRI180_MASK)
#define  NVIC_IP_PRI181_MASK                  0xFFu
#define  NVIC_IP_PRI181_SHIFT                 0u
#define  NVIC_IP_PRI181_WIDTH                 8u
#define  NVIC_IP_PRI181(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI181_SHIFT))& NVIC_IP_PRI181_MASK)
#define  NVIC_IP_PRI182_MASK                  0xFFu
#define  NVIC_IP_PRI182_SHIFT                 0u
#define  NVIC_IP_PRI182_WIDTH                 8u
#define  NVIC_IP_PRI182(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI182_SHIFT))& NVIC_IP_PRI182_MASK)
#define  NVIC_IP_PRI183_MASK                  0xFFu
#define  NVIC_IP_PRI183_SHIFT                 0u
#define  NVIC_IP_PRI183_WIDTH                 8u
#define  NVIC_IP_PRI183(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI183_SHIFT))& NVIC_IP_PRI183_MASK)
#define  NVIC_IP_PRI184_MASK                  0xFFu
#define  NVIC_IP_PRI184_SHIFT                 0u
#define  NVIC_IP_PRI184_WIDTH                 8u
#define  NVIC_IP_PRI184(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI184_SHIFT))& NVIC_IP_PRI184_MASK)
#define  NVIC_IP_PRI185_MASK                  0xFFu
#define  NVIC_IP_PRI185_SHIFT                 0u
#define  NVIC_IP_PRI185_WIDTH                 8u
#define  NVIC_IP_PRI185(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI185_SHIFT))& NVIC_IP_PRI185_MASK)
#define  NVIC_IP_PRI186_MASK                  0xFFu
#define  NVIC_IP_PRI186_SHIFT                 0u
#define  NVIC_IP_PRI186_WIDTH                 8u
#define  NVIC_IP_PRI186(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI186_SHIFT))& NVIC_IP_PRI186_MASK)
#define  NVIC_IP_PRI187_MASK                  0xFFu
#define  NVIC_IP_PRI187_SHIFT                 0u
#define  NVIC_IP_PRI187_WIDTH                 8u
#define  NVIC_IP_PRI187(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI187_SHIFT))& NVIC_IP_PRI187_MASK)
#define  NVIC_IP_PRI188_MASK                  0xFFu
#define  NVIC_IP_PRI188_SHIFT                 0u
#define  NVIC_IP_PRI188_WIDTH                 8u
#define  NVIC_IP_PRI188(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI188_SHIFT))& NVIC_IP_PRI188_MASK)
#define  NVIC_IP_PRI189_MASK                  0xFFu
#define  NVIC_IP_PRI189_SHIFT                 0u
#define  NVIC_IP_PRI189_WIDTH                 8u
#define  NVIC_IP_PRI189(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI189_SHIFT))& NVIC_IP_PRI189_MASK)
#define  NVIC_IP_PRI190_MASK                  0xFFu
#define  NVIC_IP_PRI190_SHIFT                 0u
#define  NVIC_IP_PRI190_WIDTH                 8u
#define  NVIC_IP_PRI190(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI190_SHIFT))& NVIC_IP_PRI190_MASK)
#define  NVIC_IP_PRI191_MASK                  0xFFu
#define  NVIC_IP_PRI191_SHIFT                 0u
#define  NVIC_IP_PRI191_WIDTH                 8u
#define  NVIC_IP_PRI191(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI191_SHIFT))& NVIC_IP_PRI191_MASK)
#define  NVIC_IP_PRI192_MASK                  0xFFu
#define  NVIC_IP_PRI192_SHIFT                 0u
#define  NVIC_IP_PRI192_WIDTH                 8u
#define  NVIC_IP_PRI192(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI192_SHIFT))& NVIC_IP_PRI192_MASK)
#define  NVIC_IP_PRI193_MASK                  0xFFu
#define  NVIC_IP_PRI193_SHIFT                 0u
#define  NVIC_IP_PRI193_WIDTH                 8u
#define  NVIC_IP_PRI193(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI193_SHIFT))& NVIC_IP_PRI193_MASK)
#define  NVIC_IP_PRI194_MASK                  0xFFu
#define  NVIC_IP_PRI194_SHIFT                 0u
#define  NVIC_IP_PRI194_WIDTH                 8u
#define  NVIC_IP_PRI194(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI194_SHIFT))& NVIC_IP_PRI194_MASK)
#define  NVIC_IP_PRI195_MASK                  0xFFu
#define  NVIC_IP_PRI195_SHIFT                 0u
#define  NVIC_IP_PRI195_WIDTH                 8u
#define  NVIC_IP_PRI195(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI195_SHIFT))& NVIC_IP_PRI195_MASK)
#define  NVIC_IP_PRI196_MASK                  0xFFu
#define  NVIC_IP_PRI196_SHIFT                 0u
#define  NVIC_IP_PRI196_WIDTH                 8u
#define  NVIC_IP_PRI196(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI196_SHIFT))& NVIC_IP_PRI196_MASK)
#define  NVIC_IP_PRI197_MASK                  0xFFu
#define  NVIC_IP_PRI197_SHIFT                 0u
#define  NVIC_IP_PRI197_WIDTH                 8u
#define  NVIC_IP_PRI197(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI197_SHIFT))& NVIC_IP_PRI197_MASK)
#define  NVIC_IP_PRI198_MASK                  0xFFu
#define  NVIC_IP_PRI198_SHIFT                 0u
#define  NVIC_IP_PRI198_WIDTH                 8u
#define  NVIC_IP_PRI198(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI198_SHIFT))& NVIC_IP_PRI198_MASK)
#define  NVIC_IP_PRI199_MASK                  0xFFu
#define  NVIC_IP_PRI199_SHIFT                 0u
#define  NVIC_IP_PRI199_WIDTH                 8u
#define  NVIC_IP_PRI199(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI199_SHIFT))& NVIC_IP_PRI199_MASK)
#define  NVIC_IP_PRI200_MASK                  0xFFu
#define  NVIC_IP_PRI200_SHIFT                 0u
#define  NVIC_IP_PRI200_WIDTH                 8u
#define  NVIC_IP_PRI200(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI200_SHIFT))& NVIC_IP_PRI200_MASK)
#define  NVIC_IP_PRI201_MASK                  0xFFu
#define  NVIC_IP_PRI201_SHIFT                 0u
#define  NVIC_IP_PRI201_WIDTH                 8u
#define  NVIC_IP_PRI201(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI201_SHIFT))& NVIC_IP_PRI201_MASK)
#define  NVIC_IP_PRI202_MASK                  0xFFu
#define  NVIC_IP_PRI202_SHIFT                 0u
#define  NVIC_IP_PRI202_WIDTH                 8u
#define  NVIC_IP_PRI202(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI202_SHIFT))& NVIC_IP_PRI202_MASK)
#define  NVIC_IP_PRI203_MASK                  0xFFu
#define  NVIC_IP_PRI203_SHIFT                 0u
#define  NVIC_IP_PRI203_WIDTH                 8u
#define  NVIC_IP_PRI203(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI203_SHIFT))& NVIC_IP_PRI203_MASK)
#define  NVIC_IP_PRI204_MASK                  0xFFu
#define  NVIC_IP_PRI204_SHIFT                 0u
#define  NVIC_IP_PRI204_WIDTH                 8u
#define  NVIC_IP_PRI204(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI204_SHIFT))& NVIC_IP_PRI204_MASK)
#define  NVIC_IP_PRI205_MASK                  0xFFu
#define  NVIC_IP_PRI205_SHIFT                 0u
#define  NVIC_IP_PRI205_WIDTH                 8u
#define  NVIC_IP_PRI205(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI205_SHIFT))& NVIC_IP_PRI205_MASK)
#define  NVIC_IP_PRI206_MASK                  0xFFu
#define  NVIC_IP_PRI206_SHIFT                 0u
#define  NVIC_IP_PRI206_WIDTH                 8u
#define  NVIC_IP_PRI206(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI206_SHIFT))& NVIC_IP_PRI206_MASK)
#define  NVIC_IP_PRI207_MASK                  0xFFu
#define  NVIC_IP_PRI207_SHIFT                 0u
#define  NVIC_IP_PRI207_WIDTH                 8u
#define  NVIC_IP_PRI207(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI207_SHIFT))& NVIC_IP_PRI207_MASK)
#define  NVIC_IP_PRI208_MASK                  0xFFu
#define  NVIC_IP_PRI208_SHIFT                 0u
#define  NVIC_IP_PRI208_WIDTH                 8u
#define  NVIC_IP_PRI208(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI208_SHIFT))& NVIC_IP_PRI208_MASK)
#define  NVIC_IP_PRI209_MASK                  0xFFu
#define  NVIC_IP_PRI209_SHIFT                 0u
#define  NVIC_IP_PRI209_WIDTH                 8u
#define  NVIC_IP_PRI209(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI209_SHIFT))& NVIC_IP_PRI209_MASK)
#define  NVIC_IP_PRI210_MASK                  0xFFu
#define  NVIC_IP_PRI210_SHIFT                 0u
#define  NVIC_IP_PRI210_WIDTH                 8u
#define  NVIC_IP_PRI210(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI210_SHIFT))& NVIC_IP_PRI210_MASK)
#define  NVIC_IP_PRI211_MASK                  0xFFu
#define  NVIC_IP_PRI211_SHIFT                 0u
#define  NVIC_IP_PRI211_WIDTH                 8u
#define  NVIC_IP_PRI211(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI211_SHIFT))& NVIC_IP_PRI211_MASK)
#define  NVIC_IP_PRI212_MASK                  0xFFu
#define  NVIC_IP_PRI212_SHIFT                 0u
#define  NVIC_IP_PRI212_WIDTH                 8u
#define  NVIC_IP_PRI212(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI212_SHIFT))& NVIC_IP_PRI212_MASK)
#define  NVIC_IP_PRI213_MASK                  0xFFu
#define  NVIC_IP_PRI213_SHIFT                 0u
#define  NVIC_IP_PRI213_WIDTH                 8u
#define  NVIC_IP_PRI213(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI213_SHIFT))& NVIC_IP_PRI213_MASK)
#define  NVIC_IP_PRI214_MASK                  0xFFu
#define  NVIC_IP_PRI214_SHIFT                 0u
#define  NVIC_IP_PRI214_WIDTH                 8u
#define  NVIC_IP_PRI214(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI214_SHIFT))& NVIC_IP_PRI214_MASK)
#define  NVIC_IP_PRI215_MASK                  0xFFu
#define  NVIC_IP_PRI215_SHIFT                 0u
#define  NVIC_IP_PRI215_WIDTH                 8u
#define  NVIC_IP_PRI215(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI215_SHIFT))& NVIC_IP_PRI215_MASK)
#define  NVIC_IP_PRI216_MASK                  0xFFu
#define  NVIC_IP_PRI216_SHIFT                 0u
#define  NVIC_IP_PRI216_WIDTH                 8u
#define  NVIC_IP_PRI216(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI216_SHIFT))& NVIC_IP_PRI216_MASK)
#define  NVIC_IP_PRI217_MASK                  0xFFu
#define  NVIC_IP_PRI217_SHIFT                 0u
#define  NVIC_IP_PRI217_WIDTH                 8u
#define  NVIC_IP_PRI217(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI217_SHIFT))& NVIC_IP_PRI217_MASK)
#define  NVIC_IP_PRI218_MASK                  0xFFu
#define  NVIC_IP_PRI218_SHIFT                 0u
#define  NVIC_IP_PRI218_WIDTH                 8u
#define  NVIC_IP_PRI218(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI218_SHIFT))& NVIC_IP_PRI218_MASK)
#define  NVIC_IP_PRI219_MASK                  0xFFu
#define  NVIC_IP_PRI219_SHIFT                 0u
#define  NVIC_IP_PRI219_WIDTH                 8u
#define  NVIC_IP_PRI219(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI219_SHIFT))& NVIC_IP_PRI219_MASK)
#define  NVIC_IP_PRI220_MASK                  0xFFu
#define  NVIC_IP_PRI220_SHIFT                 0u
#define  NVIC_IP_PRI220_WIDTH                 8u
#define  NVIC_IP_PRI220(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI220_SHIFT))& NVIC_IP_PRI220_MASK)
#define  NVIC_IP_PRI221_MASK                  0xFFu
#define  NVIC_IP_PRI221_SHIFT                 0u
#define  NVIC_IP_PRI221_WIDTH                 8u
#define  NVIC_IP_PRI221(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI221_SHIFT))& NVIC_IP_PRI221_MASK)
#define  NVIC_IP_PRI222_MASK                  0xFFu
#define  NVIC_IP_PRI222_SHIFT                 0u
#define  NVIC_IP_PRI222_WIDTH                 8u
#define  NVIC_IP_PRI222(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI222_SHIFT))& NVIC_IP_PRI222_MASK)
#define  NVIC_IP_PRI223_MASK                  0xFFu
#define  NVIC_IP_PRI223_SHIFT                 0u
#define  NVIC_IP_PRI223_WIDTH                 8u
#define  NVIC_IP_PRI223(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI223_SHIFT))& NVIC_IP_PRI223_MASK)
#define  NVIC_IP_PRI224_MASK                  0xFFu
#define  NVIC_IP_PRI224_SHIFT                 0u
#define  NVIC_IP_PRI224_WIDTH                 8u
#define  NVIC_IP_PRI224(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI224_SHIFT))& NVIC_IP_PRI224_MASK)
#define  NVIC_IP_PRI225_MASK                  0xFFu
#define  NVIC_IP_PRI225_SHIFT                 0u
#define  NVIC_IP_PRI225_WIDTH                 8u
#define  NVIC_IP_PRI225(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI225_SHIFT))& NVIC_IP_PRI225_MASK)
#define  NVIC_IP_PRI226_MASK                  0xFFu
#define  NVIC_IP_PRI226_SHIFT                 0u
#define  NVIC_IP_PRI226_WIDTH                 8u
#define  NVIC_IP_PRI226(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI226_SHIFT))& NVIC_IP_PRI226_MASK)
#define  NVIC_IP_PRI227_MASK                  0xFFu
#define  NVIC_IP_PRI227_SHIFT                 0u
#define  NVIC_IP_PRI227_WIDTH                 8u
#define  NVIC_IP_PRI227(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI227_SHIFT))& NVIC_IP_PRI227_MASK)
#define  NVIC_IP_PRI228_MASK                  0xFFu
#define  NVIC_IP_PRI228_SHIFT                 0u
#define  NVIC_IP_PRI228_WIDTH                 8u
#define  NVIC_IP_PRI228(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI228_SHIFT))& NVIC_IP_PRI228_MASK)
#define  NVIC_IP_PRI229_MASK                  0xFFu
#define  NVIC_IP_PRI229_SHIFT                 0u
#define  NVIC_IP_PRI229_WIDTH                 8u
#define  NVIC_IP_PRI229(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI229_SHIFT))& NVIC_IP_PRI229_MASK)
#define  NVIC_IP_PRI230_MASK                  0xFFu
#define  NVIC_IP_PRI230_SHIFT                 0u
#define  NVIC_IP_PRI230_WIDTH                 8u
#define  NVIC_IP_PRI230(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI230_SHIFT))& NVIC_IP_PRI230_MASK)
#define  NVIC_IP_PRI231_MASK                  0xFFu
#define  NVIC_IP_PRI231_SHIFT                 0u
#define  NVIC_IP_PRI231_WIDTH                 8u
#define  NVIC_IP_PRI231(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI231_SHIFT))& NVIC_IP_PRI231_MASK)
#define  NVIC_IP_PRI232_MASK                  0xFFu
#define  NVIC_IP_PRI232_SHIFT                 0u
#define  NVIC_IP_PRI232_WIDTH                 8u
#define  NVIC_IP_PRI232(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI232_SHIFT))& NVIC_IP_PRI232_MASK)
#define  NVIC_IP_PRI233_MASK                  0xFFu
#define  NVIC_IP_PRI233_SHIFT                 0u
#define  NVIC_IP_PRI233_WIDTH                 8u
#define  NVIC_IP_PRI233(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI233_SHIFT))& NVIC_IP_PRI233_MASK)
#define  NVIC_IP_PRI234_MASK                  0xFFu
#define  NVIC_IP_PRI234_SHIFT                 0u
#define  NVIC_IP_PRI234_WIDTH                 8u
#define  NVIC_IP_PRI234(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI234_SHIFT))& NVIC_IP_PRI234_MASK)
#define  NVIC_IP_PRI235_MASK                  0xFFu
#define  NVIC_IP_PRI235_SHIFT                 0u
#define  NVIC_IP_PRI235_WIDTH                 8u
#define  NVIC_IP_PRI235(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI235_SHIFT))& NVIC_IP_PRI235_MASK)
#define  NVIC_IP_PRI236_MASK                  0xFFu
#define  NVIC_IP_PRI236_SHIFT                 0u
#define  NVIC_IP_PRI236_WIDTH                 8u
#define  NVIC_IP_PRI236(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI236_SHIFT))& NVIC_IP_PRI236_MASK)
#define  NVIC_IP_PRI237_MASK                  0xFFu
#define  NVIC_IP_PRI237_SHIFT                 0u
#define  NVIC_IP_PRI237_WIDTH                 8u
#define  NVIC_IP_PRI237(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI237_SHIFT))& NVIC_IP_PRI237_MASK)
#define  NVIC_IP_PRI238_MASK                  0xFFu
#define  NVIC_IP_PRI238_SHIFT                 0u
#define  NVIC_IP_PRI238_WIDTH                 8u
#define  NVIC_IP_PRI238(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI238_SHIFT))& NVIC_IP_PRI238_MASK)
#define  NVIC_IP_PRI239_MASK                  0xFFu
#define  NVIC_IP_PRI239_SHIFT                 0u
#define  NVIC_IP_PRI239_WIDTH                 8u
#define  NVIC_IP_PRI239(x)                    (((uint8_t)(((uint8_t)(x))<< NVIC_IP_PRI239_SHIFT))& NVIC_IP_PRI239_MASK)
/* STIR Bit Fields */
#define  NVIC_STIR_INTID_MASK                 0x1FFu
#define  NVIC_STIR_INTID_SHIFT                0u
#define  NVIC_STIR_INTID_WIDTH                9u
#define  NVIC_STIR_INTID(x)                   (((uint32_t)(((uint32_t)(x))<< NVIC_STIR_INTID_SHIFT))& NVIC_STIR_INTID_MASK)

/*<! Enables an interrupt or exception */
void NVIC_EnableIRQ(IRQn_Type IRQn);

/*<! Disables an interrupt or exception.*/
void NVIC_DisableIRQ(IRQn_Type IRQn);

/*<! Sets the pending status of interrupt or exception to 1.*/
void NVIC_SetPendingIRQ(IRQn_Type IRQn);

/*<! Clears the pending status of interrupt or exception to 0. */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn);

/*<! Reads the pending status of interrupt or exception. This
function returns non-zero value if the pending status is
set to 1*/
int32_t NVIC_GetPendingIRQ(IRQn_Type IRQn);

/*<! Sets the priority of an interrupt or exception with
configurable priority level to 1.*/
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);

/*<! Reads the priority of an interrupt or exception with
configurable priority level. This function return the
current priority level.*/
uint32_t NVIC_GetPriority(IRQn_Type IRQn);

/*<! Set the priority grouping */
void NVIC_SetPriorityGrouping(uint32_t priority_grouping);

uint32_t NVIC_GetActive (IRQn_Type IRQn);

void NVIC_SystemReset (void);

#endif /* DRIVER_HEADER_DRIVER_NVIC_H_ */
