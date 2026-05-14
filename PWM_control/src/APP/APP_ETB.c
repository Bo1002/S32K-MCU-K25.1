/*
 * APP_ETB.c
 *
 *  Created on: May 13, 2026
 *      Author: BO
 */

#include "APP_ETB.h"
#include "S32K144.h"
#include "NVIC.h"

/*--- Macro ---*/
#define ADC_CHANNEL      12u
#define ADC_MAX          4095.0f
#define RPM_MAX          7800.0f
#define ENCODER_CPR      120u        /* 30 PPR x 4 (quadrature) */
#define SAMPLE_TIME_MS   10u

/*--- Driver instances (defined in their own .c files) ---*/
extern ARM_DRIVER_CAN  Driver_CAN;
extern ARM_DRIVER_PWM  Driver_PWM;
extern ADC_SIG         Driver_ADC;

/*--- Static state ---*/
static float target_rpm = 0.0f;
static float actual_rpm = 0.0f;

/*--- Forward declarations ---*/
static void CAN_UnitEvent_cb(uint32_t event);
static void CAN_ObjEvent_cb(uint32_t obj_idx, uint8_t event);
void LPIT0_Ch0_IRQHandler(void);

/************************************************************
 *  CAN Callbacks
 *  CAN_DR.c luu cac con tro nay vao static noi bo cua no,
 *  App layer chi can dinh nghia ham roi truyen vao Initialize()
 ************************************************************/
static void CAN_UnitEvent_cb(uint32_t event)
{
    (void)event;
}
static void CAN_ObjEvent_cb(uint32_t obj_idx, uint8_t event)
{
    (void)obj_idx;
    (void)event;
}
/************************************************************
 *  LPIT setup  time_ms: chu ky ngat tinh bang millisecond
 ************************************************************/
static void SetTimeTick(uint16_t time_ms)
{
    IP_PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6) | PCC_PCCn_CGC_MASK;
    IP_LPIT0->MCR                = LPIT_MCR_M_CEN_MASK;
    /* TVAL = 40MHz * time_ms / 1000 - 1 */
    IP_LPIT0->TMR[0].TVAL        = (40000000u * time_ms / 1000u) - 1u;
    IP_LPIT0->MIER               = LPIT_MIER_TIE0_MASK;
    NVIC_EnableIRQ(LPIT0_Ch0_IRQn);
    NVIC_SetPriority(LPIT0_Ch0_IRQn, 1u);
    IP_LPIT0->TMR[0].TCTRL       = LPIT_TMR_TCTRL_T_EN_MASK;
}

/************************************************************
 *  LPIT ISR  goi App_RunStep() moi 10ms
 ************************************************************/
void LPIT0_Ch0_IRQHandler(void)
{
    if (IP_LPIT0->MSR & LPIT_MSR_TIF0_MASK)
    {
        IP_LPIT0->MSR |= LPIT_MSR_TIF0_MASK;  /* W1C: ghi 1 de clear */
        App_RunStep();
    }
}

/************************************************************
 *  App_Init  khoi tao toan bo driver mot lan duy nhat
 ************************************************************/
void App_Init(void)
{
    /* --- CAN --- */
    Driver_CAN.Initialize(CAN_UnitEvent_cb, CAN_ObjEvent_cb);
    Driver_CAN.Powercontrol(ARM_POWER_ON);
    Driver_CAN.SetBitRate(ARM_CAN_BITRATE_NOMINAL, 500000u,
                           ARM_CAN_BIT_PROP_SEG(5)   |
                           ARM_CAN_BIT_PHASE_SEG1(4) |
                           ARM_CAN_BIT_PHASE_SEG2(4) |
                           ARM_CAN_BIT_SJW(1));
    Driver_CAN.ObjectConfigure(0u, ARM_CAN_OBJ_TX);   /* MB0 = TX */
    Driver_CAN.ObjectConfigure(1u, ARM_CAN_OBJ_RX);   /* MB1 = RX */
    Driver_CAN.Setmode(ARM_CAN_MODE_NORMAL);

    /* --- PWM --- */
    Driver_PWM.Initialize(NULL);
    Driver_PWM.SetFreq(1000u);
    Driver_PWM.SetDuty(0u, 0u);
    Driver_PWM.Start(0u);

    /* --- ADC --- */
    Driver_ADC.intialized(NULL);

    /* --- Encoder --- */
    ENCODER_Init();

    /* --- LPIT 10ms tick --- */
    SetTimeTick(SAMPLE_TIME_MS);
}

/************************************************************
 *  App_RunStep  chay moi 10ms tu LPIT ISR
 ************************************************************/
void App_RunStep(void)
{
    /* 1. Doc potentiometer -> setpoint */
    uint32_t adc_val = (uint32_t)Driver_ADC.Readadc(ADC_CHANNEL);
    target_rpm = ((float)adc_val / ADC_MAX) * RPM_MAX;

    /* 2. Doc encoder -> toc do thuc */
    int16_t delta = ENCODER_GetDelta();
    actual_rpm = (float)delta * (1000.0f / SAMPLE_TIME_MS) * 60.0f / ENCODER_CPR;

    /* 3. TODO: PID -> duty cycle */

    /* 4. TODO: gui CAN actual_rpm len Arduino */
}

/************************************************************
 *  Public API
 ************************************************************/
void App_SetTargetRPM(float rpm)
{
    target_rpm = rpm;
}

float App_GetActualRPM(void)
{
    return actual_rpm;
}
