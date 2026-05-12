#include "CAN_DR.H"

#include <S32K144.h>



#define FLEXCAN_RX 12
#define FLEXCAN_TX 13   


/* save Callback impulse first initialized*/
static ARM_CAN_SignalUnitEvent_t CAN_cb_event  = NULL;
static ARM_Can_SignalObjectEvent_t CAN_cb_object = NULL;

/*Driver state */
static uint8_t can_initialized = 0;
static uint8_t can_powered     = 0;

/*************************PROTOCAL***************************/
static void CAN_0_PortC();


static ARM_DRIVER_VERSION    CAN_GetVersion       (void);
static ARM_CAN_CAPABILITIES  CAN_GetCapabilities  (void);
static int32_t               CAN_Initialize       (ARM_CAN_SignalUnitEvent_t cb_event, ARM_Can_SignalObjectEvent_t cb_Ob_event);
static int32_t               CAN_Uninitialize     (void);
static int32_t               CAN_PowerControl     (ARM_POWER_STATE state);
static uint32_t              CAN_GetClock         (void);
static int32_t               CAN_SetBitRate       (ARM_CAN_BITRATE_SELECT, uint32_t, uint32_t);
static int32_t               CAN_SetMode          (ARM_CAN_MODE mode);
static ARM_CAN_OBJ_CAPABILITIES CAN_ObjectGetCapabilities (uint32_t obj_idx);
static int32_t               CAN_ObjectSetFilter  (uint32_t, ARM_CAN_FILTER_OPERATION, uint32_t, uint32_t);
static int32_t               CAN_ObjectConfigure  (uint32_t, ARM_CAN_OBJ_CONFIG);
static int32_t               CAN_MessageSend      (uint32_t, ARM_CAN_MSG_INFO*, const uint8_t*, uint8_t);
static int32_t               CAN_MessageRead      (uint32_t, ARM_CAN_MSG_INFO*, const uint8_t*, uint8_t);
static int32_t               CAN_Control          (uint32_t, uint32_t);
static ARM_CAN_STATUS        CAN_GetStatus        (void);
/*************************IMPELMENTED**********************************/
static void CAN_0_PortC()
{   
    IP_PCC->PCCn[PCC_PORTA_INDEX] |= PCC_PCCn_CGC_MASK;
    IP_PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK;
    
    IP_PORTA->PCR[FLEXCAN_RX] = PORT_PCR_MUX(5);
    IP_PORTA->PCR[FLEXCAN_TX] = PORT_PCR_MUX(5);

    for  (uint8_t i = 0; i < 128; i++)
    {
        IP_FLEXCAN0->RAMn[i] = 0; 
    }
    
    /*ENABLE CAN MODULE */
    IP_FLEXCAN0->MCR &= ~ (FLEXCAN_MCR_MDIS_MASK | FLEXCAN_MCR_FRZ_MASK);

    while((IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));

    /* Enable freeze mode*/ 
    IP_FLEXCAN0->MCR |=  FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK; 
    while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));
}


/*ARM get version*/
static ARM_DRIVER_VERSION  CAN_GetVersion(void)
{
    ARM_DRIVER_VERSION ver = {.api = 0x0010, .drv = 0x0010};
    return ver; 
}

static ARM_CAN_CAPABILITIES  CAN_GetCapabilities  (void)
{
    ARM_CAN_CAPABILITIES Getcab=
    {
        .num_object = 8,
        .reentrant_operation = 1,
        .fd_mode = 0,
        .internal_loopback = 0,
        .monitor_mode = 0,
        .restricted_mode = 0,
        .external_loopback  = 0,
        .reserved = 0
    };
    return Getcab;
} 

static int32_t CAN_Initialize (ARM_CAN_SignalUnitEvent_t cb_event, ARM_Can_SignalObjectEvent_t cb_Ob_event)
{
    CAN_cb_event = cb_event; 
    CAN_cb_object = cb_Ob_event;
    CAN_0_PortC();
    can_initialized = 1;
    return ARM_DRIVER_OK;
}


static int32_t  CAN_Uninitialize   (void)
{
    if(!can_initialized)
    {
        return ARM_DRIVER_ERROR;
    }
    CAN_cb_event = NULL;
    CAN_cb_object = NULL;
    can_initialized = 0;
    can_powered = 0;
    IP_FLEXCAN0->MCR |= FLEXCAN_MCR_MDIS_MASK;

    return ARM_DRIVER_OK ;
}

static int32_t   CAN_PowerControl  (ARM_POWER_STATE state)
{
    if(!can_initialized)
    {
        return ARM_DRIVER_ERROR;
    }

    switch (state)
    {
    case ARM_POWER_ON:
        IP_FLEXCAN0->MCR &= ~FLEXCAN_MCR_MDIS_MASK;  // bật module
        can_powered = 1;
        return ARM_DRIVER_OK;
        break;

    case ARM_POWER_OFF:
        IP_FLEXCAN0->MCR |= FLEXCAN_MCR_MDIS_MASK;   // tắt module
        can_powered = 0;
        return ARM_DRIVER_OK;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}


static uint32_t CAN_GetClock(void)
{
    return 80000000U;
}



static int32_t   CAN_SetBitRate(ARM_CAN_BITRATE_SELECT select, uint32_t bitrate, uint32_t segment)
{
    if(!can_initialized)    return ARM_DRIVER_ERROR;
    if(bitrate == 0)        return ARM_DRIVER_ERROR_PARAMETER; 

    switch (select)
    {
    case ARM_CAN_BITRATE_NOMINAL:
        uint8_t prop = (segment & ARM_CAN_BIT_PROP_SEG_Msk)   >> ARM_CAN_BIT_PROP_SEG_Pos;
        uint8_t seg1 = (segment & ARM_CAN_BIT_PHASE_SEG1_Msk) >> ARM_CAN_BIT_PHASE_SEG1_Pos;
        uint8_t seg2 = (segment & ARM_CAN_BIT_PHASE_SEG2_Msk) >> ARM_CAN_BIT_PHASE_SEG2_Pos;
        uint8_t sjw  = (segment & ARM_CAN_BIT_SJW_Msk)        >> ARM_CAN_BIT_SJW_Pos;
        uint32_t total_tq = 1U + prop + seg1 + seg2;
        uint32_t presdiv  = ((80000000U / (bitrate * total_tq)) - 1U );

        IP_FLEXCAN0->CTRL1  =     FLEXCAN_CTRL1_PRESDIV(presdiv)
                                | FLEXCAN_CTRL1_PROPSEG(prop - 1u)
                                | FLEXCAN_CTRL1_PSEG1(seg1 -1u)
                                | FLEXCAN_CTRL1_PSEG2(seg2 - 1u)
                                | FLEXCAN_CTRL1_RJW(sjw - 1u) ;
        return ARM_DRIVER_OK;
        break;
    
    default:
    return ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
}

static int32_t  CAN_SetMode(ARM_CAN_MODE mode)
{
    if(!can_initialized) return ARM_DRIVER_ERROR;

    switch (mode)
    {
    case ARM_CAN_MODE_INITIALIZATION:
        IP_FLEXCAN0->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK;
        while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));

        return ARM_DRIVER_OK;
        break;
    
    case ARM_CAN_MODE_NORMAL:
        /*get in frz mode and clear bit mode */
        IP_FLEXCAN0->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK;
        while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));
        /*turn off LOM and LPB*/

        IP_FLEXCAN0->CTRL1 &= ~(FLEXCAN_CTRL1_LOM_MASK | FLEXCAN_CTRL1_LPB_MASK);
        /*turn off frz mode */
        IP_FLEXCAN0->MCR &= ~(FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK);
        while(IP_FLEXCAN0-> MCR & FLEXCAN_MCR_NOTRDY_MASK);
        return ARM_DRIVER_OK;
    
    case ARM_CAN_MODE_RESTRICTED:
    case ARM_CAN_MODE_MONITOR:
        /*Get in frz mode to change CTRL1*/
        IP_FLEXCAN0->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK;
        while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK));
        /*Listen only: receive but no transmit, unsend ACK*/
        IP_FLEXCAN0->CTRL1 |= FLEXCAN_CTRL1_LOM_MASK;
        /*Turn off frz*/
        IP_FLEXCAN0->MCR &= ~(FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK);
        while(IP_FLEXCAN0->MCR & FLEXCAN_MCR_NOTRDY_MASK);
        return ARM_DRIVER_OK;

    case ARM_CAN_MODE_LOOPBACK_INTERNAL:
        IP_FLEXCAN0->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK; 
        while(!(IP_FLEXCAN0->MCR & FLEXCAN_MCR_FRZACK_MASK)); 
        /*LPB =1: TX nối bộ vào RX, chân TX ra bus luôn recessive*/
        IP_FLEXCAN0->CTRL1 |= FLEXCAN_CTRL1_LPB_MASK; 
        IP_FLEXCAN0->CTRL1 &= ~FLEXCAN_CTRL1_LOM_MASK;
        IP_FLEXCAN0 -> MCR &= ~(FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK);
        while(IP_FLEXCAN0->MCR & FLEXCAN_MCR_NOTRDY_MASK);
        return ARM_DRIVER_OK;

    case ARM_CAN_MODE_LOOPBACK_EXTERNAL: 

        IP_FLEXCAN0->MCR |= FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK; 
        while(!(IP_FLEXCAN0 -> MCR & FLEXCAN_MCR_FRZACK_MASK)); 
        /*LPB1= 1 nhưng LOM= 0: vừa loop back vừa ra bus*/
        IP_FLEXCAN0->CTRL1 |= FLEXCAN_CTRL1_LPB_MASK; 
        IP_FLEXCAN0->CTRL1  &= ~(FLEXCAN_CTRL1_LOM_MASK); 
        IP_FLEXCAN0->MCR &= ~(FLEXCAN_MCR_FRZ_MASK | FLEXCAN_MCR_HALT_MASK); 
        while(IP_FLEXCAN0->MCR & FLEXCAN_MCR_NOTRDY_MASK); 
        return ARM_DRIVER_OK;

    default:
        return ARM_DRIVER_ERROR_UNSUPPORTED; 
        break;
    }
}

static ARM_CAN_OBJ_CAPABILITIES CAN_ObjectGetCapabilities (uint32_t obj_idx)
{
    ARM_CAN_OBJ_CAPABILITIES cap = {0}; 
    if(obj_idx == 0U)
    {
        cap.tx              = 1;
        cap.exact_filtering = 1;
    }  
    else if(obj_idx == 1U)
    {
        cap.rx              = 1;
        cap.exact_filtering = 1;
        cap.mask_filtering  = 1; 
    }
    return cap;
}

static int32_t CAN_ObjectSetFilter(uint32_t obj_idx, ARM_CAN_FILTER_OPERATION operation,
                                    uint32_t id, uint32_t arg)
{
    if (!can_initialized) return ARM_DRIVER_ERROR;
    if (obj_idx != 1U)    return ARM_DRIVER_ERROR_UNSUPPORTED;

    switch (operation)
    {
        case ARM_CAN_FILTER_ID_EXACT_ADD:
            IP_FLEXCAN0->RXMGMASK = 0x1FFFFFFFU;        /* tất cả bit phải khớp */
            IP_FLEXCAN0->RAMn[5]  = (id & 0x7FFU) << 18U;
            return ARM_DRIVER_OK;

        case ARM_CAN_FILTER_ID_MASKABLE_ADD:
            IP_FLEXCAN0->RXMGMASK = (arg & 0x7FFU) << 18U; /* mask tùy chỉnh */
            IP_FLEXCAN0->RAMn[5]  = (id  & 0x7FFU) << 18U;
            return ARM_DRIVER_OK;

        case ARM_CAN_FILTER_ID_EXACT_REMOVE:
        case ARM_CAN_FILTER_ID_MASKABLE_REMOVE:
            IP_FLEXCAN0->RXMGMASK = 0U;  /* chấp nhận tất cả */
            return ARM_DRIVER_OK;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

static int32_t CAN_ObjectConfigure(uint32_t obj_idx, ARM_CAN_OBJ_CONFIG obj_cfg)
{
    if (!can_initialized) return ARM_DRIVER_ERROR;
    if (obj_idx > 7U)     return ARM_DRIVER_ERROR_PARAMETER;

    uint32_t base = obj_idx * 4U;

    switch (obj_cfg)
    {
        case ARM_CAN_OBJ_INACTIVE:
            IP_FLEXCAN0->RAMn[base] = 0x08000000U;  /* CODE = INACTIVE */
            return ARM_DRIVER_OK;

        case ARM_CAN_OBJ_TX:
            IP_FLEXCAN0->RAMn[base] = 0x08000000U;  /* INACTIVE, sẵn sàng TX */
            return ARM_DRIVER_OK;

        case ARM_CAN_OBJ_RX:
            IP_FLEXCAN0->RAMn[base] = 0x04080000U;  /* CODE = EMPTY, DLC = 8 */
            return ARM_DRIVER_OK;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

static int32_t CAN_MessageSend(uint32_t obj_idx, ARM_CAN_MSG_INFO *msg_info,
                                const uint8_t *data, uint8_t size)
{
    if (!can_initialized || !can_powered) return ARM_DRIVER_ERROR;
    if (obj_idx > 7U || size > 8U)        return ARM_DRIVER_ERROR_PARAMETER;

    uint32_t base = obj_idx * 4U;
    uint32_t id   = msg_info->id & 0x7FFU;

    IP_FLEXCAN0->IFLAG1         = (1U << obj_idx);   /* clear TX flag */
    IP_FLEXCAN0->RAMn[base]     = 0x08000000U;        /* INACTIVE */
    IP_FLEXCAN0->RAMn[base + 1] = id << 18U;
    IP_FLEXCAN0->RAMn[base + 2] = ((uint32_t)data[0] << 24U)
                                 | ((uint32_t)data[1] << 16U)
                                 | ((uint32_t)data[2] <<  8U)
                                 |  (uint32_t)data[3];
    IP_FLEXCAN0->RAMn[base + 3] = ((uint32_t)data[4] << 24U)
                                 | ((uint32_t)data[5] << 16U)
                                 | ((uint32_t)data[6] <<  8U)
                                 |  (uint32_t)data[7];
    IP_FLEXCAN0->RAMn[base]     = (0x0CU << 24U)      /* CODE = TX */
                                 | ((uint32_t)size << 16U);
    return ARM_DRIVER_OK;
}

static int32_t CAN_MessageRead(uint32_t obj_idx, ARM_CAN_MSG_INFO *msg_info,
                                const uint8_t *data, uint8_t size)
{
    if (!can_initialized) return ARM_DRIVER_ERROR;
    if (obj_idx > 7U)     return ARM_DRIVER_ERROR_PARAMETER;

    if (!(IP_FLEXCAN0->IFLAG1 & (1U << obj_idx)))
        return ARM_DRIVER_ERROR_BUSY;   /* chưa có frame mới */

    uint32_t base  = obj_idx * 4U;
    uint32_t word0 = IP_FLEXCAN0->RAMn[base + 2];
    uint32_t word1 = IP_FLEXCAN0->RAMn[base + 3];

    msg_info->id  = (IP_FLEXCAN0->RAMn[base + 1] >> 18U) & 0x7FFU;
    msg_info->dlc = (IP_FLEXCAN0->RAMn[base]     >> 16U) & 0xFU;

    uint8_t *buf = (uint8_t *)data;
    buf[0] = (word0 >> 24U) & 0xFFU;
    buf[1] = (word0 >> 16U) & 0xFFU;
    buf[2] = (word0 >>  8U) & 0xFFU;
    buf[3] = (word0       ) & 0xFFU;
    buf[4] = (word1 >> 24U) & 0xFFU;
    buf[5] = (word1 >> 16U) & 0xFFU;
    buf[6] = (word1 >>  8U) & 0xFFU;
    buf[7] = (word1       ) & 0xFFU;

    IP_FLEXCAN0->IFLAG1 = (1U << obj_idx);  /* clear flag */
    return ARM_DRIVER_OK;
}

static int32_t CAN_Control(uint32_t control, uint32_t arg)
{
    if (!can_initialized) return ARM_DRIVER_ERROR;

    switch (control)
    {
        case ARM_CAN_ABORT_MESSAGE_SEND:
            if (arg > 7U) return ARM_DRIVER_ERROR_PARAMETER;
            IP_FLEXCAN0->RAMn[arg * 4U] = 0x08000000U;  /* INACTIVE = abort */
            return ARM_DRIVER_OK;

        case ARM_CAN_CONTROL_RETRANSMISSION:
            if (arg == 0U)
                IP_FLEXCAN0->MCR |=  FLEXCAN_MCR_AEN_MASK;
            else
                IP_FLEXCAN0->MCR &= ~FLEXCAN_MCR_AEN_MASK;
            return ARM_DRIVER_OK;

        default:
            return ARM_DRIVER_ERROR_UNSUPPORTED;
    }
}

static ARM_CAN_STATUS CAN_GetStatus(void)
{
    ARM_CAN_STATUS status = { 0 };
    uint32_t esr1 = IP_FLEXCAN0->ESR1;
    uint32_t ecr  = IP_FLEXCAN0->ECR;

    if (IP_FLEXCAN0->MCR & FLEXCAN_MCR_MDIS_MASK)
        status.unit_state = ARM_CAN_UNIT_STATE_INACTIVE;
    else if (esr1 & FLEXCAN_ESR1_BOFFINT_MASK)
        status.unit_state = ARM_CAN_UNIT_STATE_BUS_OFF;
    else if (esr1 & FLEXCAN_ESR1_ERRINT_MASK)
        status.unit_state = ARM_CAN_UNIT_STATE_PASSIVE;
    else
        status.unit_state = ARM_CAN_UNIT_STATE_ACTIVE;

    status.tx_error_count = (ecr & FLEXCAN_ECR_TXERRCNT_MASK)
                            >> FLEXCAN_ECR_TXERRCNT_SHIFT;
    status.rx_error_count = (ecr & FLEXCAN_ECR_RXERRCNT_MASK)
                            >> FLEXCAN_ECR_RXERRCNT_SHIFT;

    return status;
}


ARM_DRIVER_CAN Driver_CAN = {
    CAN_GetVersion,
    CAN_GetCapabilities,
    CAN_Initialize,
    CAN_Uninitialize,
    CAN_PowerControl,
    CAN_GetClock,
    CAN_SetBitRate,
    CAN_SetMode,
    CAN_ObjectGetCapabilities,
    CAN_ObjectSetFilter,
    CAN_ObjectConfigure,
    CAN_MessageSend,
    CAN_MessageRead,
    CAN_Control,
    CAN_GetStatus
};