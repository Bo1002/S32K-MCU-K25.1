/**
 * @file CAN_DR.H
 * @author Nguyen Dinh Minh Vuong (you@domain.com)
 * @brief  This Driver deved by CMSIS Standard provied by ARM. 
 * @version 0.1
 * @date 2026-05-09
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef CAN_DR_H
#define CAN_DR_H
#include "common_driver.h"
#include <stdint.h>

#ifdef  __cplusplus
extern "C"
{
#endif

/*Status code CAN DRIVER*/
#define 	ARM_CAN_UNIT_STATE_INACTIVE   (0U)
/*Unit state: Not active on bus (initialization)*/
 
#define 	ARM_CAN_UNIT_STATE_ACTIVE     (1U)
//	Unit state: Active on bus (can generate active error frame)
 
#define 	ARM_CAN_UNIT_STATE_PASSIVE    (2U)
//Unit state: Error passive (can not generate active error frame)
 
#define 	ARM_CAN_UNIT_STATE_BUS_OFF    (3U)
//Unit state: Bus-off (can recover to active state)
 
#define 	ARM_CAN_LEC_NO_ERROR      (0U)
//Last error code: No error.
 
#define 	ARM_CAN_LEC_BIT_ERROR     (1U)
//Last error code: Bit error.
 
#define 	ARM_CAN_LEC_STUFF_ERROR   (2U)
//Last error code: Bit stuffing error.
 
#define 	ARM_CAN_LEC_CRC_ERROR     (3U)
//Last error code: CRC error.
 
#define 	ARM_CAN_LEC_FORM_ERROR    (4U)
//Last error code: Illegal fixed-form bit.
 
#define 	ARM_CAN_LEC_ACK_ERROR     (5U)
//Last error code: Acknowledgment error.
 

/**
 * @brief Callback unit events notified via ARM_CAN_SignalUnitEvent.
The CAN driver generates callback unit events that are notified via the function ARM_CAN_SignalUnitEvent.
 * 
 */

/* Unit entered Inactive state*/
 #define 	ARM_CAN_EVENT_UNIT_INACTIVE   (0U)

/* Unit entered Error Active state.*/
#define 	ARM_CAN_EVENT_UNIT_ACTIVE     (1U)

/* 	Unit entered Error Warning state (one or both error counters >= 96)*/
#define 	ARM_CAN_EVENT_UNIT_WARNING    (2U)

/*Unit entered Error Passive state.*/ 
#define 	ARM_CAN_EVENT_UNIT_PASSIVE    (3U)
 	
/*Unit entered Bus-off state.*/
#define 	ARM_CAN_EVENT_UNIT_BUS_OFF    (4U)
 /**********************************************/	
 


/**
 * @brief Callback objects events notified via ARM_CAN_SignalObjectEvent.
The CAN driver generates callback objects events that are notified via the function ARM_CAN_SignalObjectEvent.
 * 
 */
/*Send complete.*/
#define 	ARM_CAN_EVENT_SEND_COMPLETE     (1UL << 0)

/*Message received.*/
#define 	ARM_CAN_EVENT_RECEIVE           (1UL << 1)
 	
/*Received message overrun.*/
#define 	ARM_CAN_EVENT_RECEIVE_OVERRUN   (1UL << 2)

 /***************************************************************/


/**
 * @brief ARM CAN indentifier
 *  Set object to Standard or extend
 * 
 */
/*11-bit*/
#define ARM_CAN_STANDARD_ID(id)    (id & 0x000007FFUL) 
/*29-bit*/
#define ARM_CAN_EXTEND_ID(id)      ((id & 0x1FFFFFFFUL) | ARM_CAN_ID_IDE_Msk)
/***********************************/


/**
 * @brief Set CAN operation modes
 * CAN Operation using the function ARM_CAN_CONTROL
 * 
 */

#define     ARM_CAN_BIT_PROP_SEG_Pos    0u
#define     ARM_CAN_BIT_PROP_SEG_Msk    (0xFFUL)
#define     ARM_CAN_BIT_PHASE_SEG1_Pos  8u
#define     ARM_CAN_BIT_PHASE_SEG1_Msk  (0XFFUL << 8U)
#define     ARM_CAN_BIT_PHASE_SEG2_Pos  16U
#define     ARM_CAN_BIT_PHASE_SEG2_Msk  (0XFFUL << 16U)
#define     ARM_CAN_BIT_SJW_Pos         24U
#define     ARM_CAN_BIT_SJW_Msk         (0XFFUL << 24U)

#define     ARM_CAN_CONTROL_Pos         0u

#define     ARM_CAN_CONTROL_Msk         (0xFFUL << ARM_CAN_CONTROL_Pos)

/*	Set FD operation mode; arg: 0 = disable, 1 = enable. */
#define   ARM_CAN_SET_FD_MODE              (1UL << ARM_CAN_CONTROL_Pos)

/* Abort sending of CAN message; arg = object.*/
#define 	ARM_CAN_ABORT_MESSAGE_SEND       (2UL << ARM_CAN_CONTROL_Pos)

/* 	Enable/disable automatic retransmission; arg: 0 = disable, 1 = enable (default state)*/
#define 	ARM_CAN_CONTROL_RETRANSMISSION   (3UL << ARM_CAN_CONTROL_Pos)   

/*Set transceiver delay; arg = delay in time quanta.*/
#define 	ARM_CAN_SET_TRANSCEIVER_DELAY    (4UL << ARM_CAN_CONTROL_Pos)

/***************************/


/**
 * @brief Set initialized CAN bus
 * parameter for ARM_CAN_MODE
 */
typedef enum  {
  ARM_CAN_MODE_INITIALIZATION ,
  ARM_CAN_MODE_NORMAL ,
  ARM_CAN_MODE_RESTRICTED ,
  ARM_CAN_MODE_MONITOR ,
  ARM_CAN_MODE_LOOPBACK_INTERNAL ,
  ARM_CAN_MODE_LOOPBACK_EXTERNAL
}ARM_CAN_MODE;

/***************************************************/

/**
 * @brief Set bit timing
 * used with the function ARM_CAN_SetBitrate.
 */

 
#define 	ARM_CAN_BIT_PROP_SEG(x)     (((x) << ARM_CAN_BIT_PROP_SEG_Pos) & ARM_CAN_BIT_PROP_SEG_Msk)
 
#define 	ARM_CAN_BIT_PHASE_SEG1(x)   (((x) << ARM_CAN_BIT_PHASE_SEG1_Pos) & ARM_CAN_BIT_PHASE_SEG1_Msk)
 
#define 	ARM_CAN_BIT_PHASE_SEG2(x)   (((x) << ARM_CAN_BIT_PHASE_SEG2_Pos) & ARM_CAN_BIT_PHASE_SEG2_Msk)
 
#define 	ARM_CAN_BIT_SJW(x)          (((x) << ARM_CAN_BIT_SJW_Pos) & ARM_CAN_BIT_SJW_Msk)

typedef enum
{
  ARM_CAN_BITRATE_NOMINAL ,
  ARM_CAN_BITRATE_FD_DATA
} ARM_CAN_BITRATE_SELECT;

 /***************************/

/**
 * @brief Set CAN filter manipulation codes.
 * 
 */

 typedef enum
 {
  ARM_CAN_FILTER_ID_EXACT_ADD ,
  ARM_CAN_FILTER_ID_EXACT_REMOVE ,
  ARM_CAN_FILTER_ID_RANGE_ADD ,
  ARM_CAN_FILTER_ID_RANGE_REMOVE ,
  ARM_CAN_FILTER_ID_MASKABLE_ADD ,
  ARM_CAN_FILTER_ID_MASKABLE_REMOVE
} ARM_CAN_FILTER_OPERATION;

 /**********************************************/

/**
 * @brief CAN Object Configuration codes.
 * 
 */
typedef enum 
{
  ARM_CAN_OBJ_INACTIVE ,
  ARM_CAN_OBJ_TX ,
  ARM_CAN_OBJ_RX ,
  ARM_CAN_OBJ_RX_RTR_TX_DATA , //CAN object that on RTR reception automatically transmits Data Frame.
  ARM_CAN_OBJ_TX_RTR_RX_DATA   //CAN object that transmits RTR and automatically receives Data Frame.
}ARM_CAN_OBJ_CONFIG;

/**********************************/

/**
 * @brief A CAN drive with different capabilities encoded in the data fields of this structure.
 * 
 */
typedef struct 
{
    uint32_t    num_object :8;          //Number of CAN Message Objects available.
    uint32_t	reentrant_operation: 1;	//Support for reentrant calls to ARM_CAN_MessageSend, ARM_CAN_MessageRead, ARM_CAN_ObjectConfigure and abort message sending used by ARM_CAN_Control.
    uint32_t	fd_mode: 1;	            //Support for CAN with flexible data-rate mode (CAN_FD) (set by ARM_CAN_Control)
    uint32_t	restricted_mode: 1;	    //Support for restricted operation mode (set by ARM_CAN_SetMode)
    uint32_t	monitor_mode: 1;	    //Support for bus monitoring mode (set by ARM_CAN_SetMode)
    uint32_t	internal_loopback: 1;	//Support for internal loopback mode (set by ARM_CAN_SetMode)
    uint32_t	external_loopback: 1;	//Support for external loopback mode (set by ARM_CAN_SetMode)
    uint32_t	reserved: 18;	        //Reserved (must be zero)

}ARM_CAN_CAPABILITIES;
/****************************************************************/



/**
 * @brief Structure with information about the status of the CAN unit state and errors. 
 * The data fields encode the unit bus state, last error code, transmitter error count, and receiver error count.
 * 
 */

typedef struct
{ 
    uint32_t	unit_state: 4;	    //Unit bus state.
    uint32_t	last_error_code: 4;	//Last error code.
    uint32_t	tx_error_count: 8;	//Transmitter error count.
    uint32_t	rx_error_count: 8;	//Receiver error count.
    uint32_t	reserved: 8; 
}ARM_CAN_STATUS;

/***************************************************/


/**
 * @brief Structure with information about the CAN message.

In CAN mode, the following ARM_CAN_MSG_INFO data fields are ignored: edl, brs, esi.
In CAN FD mode, the following ARM_CAN_MSG_INFO data field is ignored: rtr.
 * 
 */
typedef struct {
    uint32_t	id;	            //CAN identifier with frame format specifier (bit 31)
    uint32_t	rtr: 1;	        //Remote transmission request frame.
    uint32_t	edl: 1;	        //Flexible data-rate format extended data length.
    uint32_t	brs: 1;	        //Flexible data-rate format with bitrate switch.
    uint32_t	esi: 1;	        //Flexible data-rate format error state indicator.
    uint32_t	dlc: 4;	        //Data length code.
    uint32_t	reserved: 24;	
} ARM_CAN_MSG_INFO;

/*******************************************************************************/

/**
 * @brief A CAN object can be implemented with different capabilities encoded in the data fields of this structure.
 * 
 */
typedef struct 
{
    uint32_t	tx:               1;	    //Object supports transmission.
    uint32_t	rx:               1;	    //Object supports reception.
    uint32_t	rx_rtr_tx_data:   1;	    //Object supports RTR reception and automatic Data Frame transmission.
    uint32_t	tx_rtr_rx_data:   1;	    //Object supports RTR transmission and automatic Data Frame reception.
    uint32_t	multiple_filters: 1;	    //Object allows assignment of multiple filters to it.
    uint32_t	exact_filtering:  1;	    //Object supports exact identifier filtering.
    uint32_t	range_filtering:  1;	    //Object supports range identifier filtering.
    uint32_t	mask_filtering:   1;	    //Object supports mask identifier filtering.
    uint32_t	message_depth:    8;	    //Number of messages buffers (FIFO) for that object.
    uint32_t	reserved:         16;	    //Reserved (must be zero)
}ARM_CAN_OBJ_CAPABILITIES;
/***************************************************************************/

typedef void (*ARM_CAN_SignalUnitEvent_t )(uint32_t event);
typedef void (*ARM_Can_SignalObjectEvent_t ) (uint32_t obj_idx, uint8_t event);


typedef struct
{
    ARM_DRIVER_VERSION   (*Getversion) (void);
    ARM_CAN_CAPABILITIES (*GetCapabilities) (void);
    
    int32_t (*Initialize)(ARM_CAN_SignalUnitEvent_t cb_unit_event, ARM_Can_SignalObjectEvent_t cb_Object_evnet); //Pointer to ARM_CAN_Initialize : Initialize CAN interface.

    int32_t (*Uninitialize)(void);
    int32_t (*Powercontrol) (ARM_POWER_STATE state);
    uint32_t (*GetClock)(void); 
    int32_t  (*SetBitRate)(ARM_CAN_BITRATE_SELECT select, uint32_t Bitrate, uint32_t bit_segment); 
    int32_t (*Setmode)(ARM_CAN_MODE mode);

    ARM_CAN_OBJ_CAPABILITIES (* ObjectGetcapabilities)(uint32_t obj_idx);
    
    int32_t (*ObjectSelectFilter)(uint32_t obj_idx, ARM_CAN_FILTER_OPERATION operation, uint32_t id, uint32_t arg);
    int32_t (*ObjectConfigure)(uint32_t obj_idx, ARM_CAN_OBJ_CONFIG obj_cfg);

    int32_t (*MessageSend) (uint32_t  obj_inx, ARM_CAN_MSG_INFO *msg_info, const uint8_t *data, uint8_t size);
    int32_t (*MessageRead) (uint32_t  obj_inx, ARM_CAN_MSG_INFO *msg_info, const uint8_t *data, uint8_t size); 
    int32_t (*control)(uint32_t control, uint32_t arg);
    ARM_CAN_STATUS (*GetStatus)(void);
}ARM_DRIVER_CAN;

#ifdef  __cplusplus
}
#endif


 #endif