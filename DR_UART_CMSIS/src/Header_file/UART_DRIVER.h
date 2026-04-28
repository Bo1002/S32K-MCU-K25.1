/**
 * @file UART_DRIVER.h
 * @author Minh Vuong (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-10-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_common.h"


/*Arm  Driver*/
#define ARM_USART_API_VERSION   ARM_DRIVER_VERSION_MAJOR_MINOR(2,4) /* API version */

#define _ARM_Driver_USART_	(n)	   Driver_USART##n

#define ARM_Driver_USART_	(n)	   _ARM_Driver_USART_(n)



/*Arm con control*/
#define ARM_USART_CONTROL_Pos   0
#define ARM_USART_CONTROL_Msk   (0xFFUL << ARM_USART_CONTROL_Pos)

#define ARM_USART_DATA_BITS_Pos   8
#define ARM_USART_DATA_BITS_Msk   (7UL << ARM_USART_DATA_BITS_Pos)

#define ARM_USART_PARITY_Pos   12
#define ARM_USART_PARITY_Msk   (3UL << ARM_USART_PARITY_Pos)

#define ARM_USART_STOP_BITS_Pos   14
#define ARM_USART_STOP_BITS_Msk   (3UL << ARM_USART_STOP_BITS_Pos)

#define ARM_USART_FLOW_CONTROL_Pos   16
#define ARM_USART_FLOW_CONTROL_Msk   (3UL << ARM_USART_FLOW_CONTROL_Pos)

#define ARM_USART_CPOL_Pos   18
#define ARM_USART_CPOL_Msk   (1UL << ARM_USART_CPOL_Pos)

#define ARM_USART_CPHA_Pos   19
#define ARM_USART_CPHA_Msk   (1UL << ARM_USART_CPHA_Pos)


/**
 * @brief This support for UART erro 
 * 
 */
/*Specified Mode not supported*/
#define 	ARM_USART_ERROR_MODE   (ARM_DRIVER_ERROR_SPECIFIC - 1)
/*Specified baudrate not supported.*/
#define 	ARM_USART_ERROR_BAUDRATE   (ARM_DRIVER_ERROR_SPECIFIC - 2)
/*Specified number of Data bits not supported.*/
#define 	ARM_USART_ERROR_DATA_BITS   (ARM_DRIVER_ERROR_SPECIFIC - 3)
/*Specified Parity not supported.*/
#define 	ARM_USART_ERROR_PARITY   (ARM_DRIVER_ERROR_SPECIFIC - 4)
/*Specified number of Stop bits not supported.*/
#define 	ARM_USART_ERROR_STOP_BITS   (ARM_DRIVER_ERROR_SPECIFIC - 5)
/*Specified Flow Control not supported.*/
#define 	ARM_USART_ERROR_FLOW_CONTROL   (ARM_DRIVER_ERROR_SPECIFIC - 6)
/*Specified Clock Polarity not supported.*/
#define 	ARM_USART_ERROR_CPOL   (ARM_DRIVER_ERROR_SPECIFIC - 7)
/*Specified Clock Phase not supported.*/
#define 	ARM_USART_ERROR_CPHA   (ARM_DRIVER_ERROR_SPECIFIC - 8)


/**
 * @brief UART: Events: this The USART driver generates call back events that are notified via the function ARM_USART_SignalEvent
 * 
 */
/*Send completed; however USART may still transmit data.*/
#define 	ARM_USART_EVENT_SEND_COMPLETE   (1UL << 0)
/*Receive completed.*/
#define 	ARM_USART_EVENT_RECEIVE_COMPLETE   (1UL << 1)
/*Transfer completed.*/
#define 	ARM_USART_EVENT_TRANSFER_COMPLETE   (1UL << 2)
/*Transmit completed (optional)*/
#define 	ARM_USART_EVENT_TX_COMPLETE   (1UL << 3)
/*Transmit data not available (Synchronous Slave)*/
#define 	ARM_USART_EVENT_TX_UNDERFLOW   (1UL << 4)
/*Receive data overflow.*/
#define 	ARM_USART_EVENT_RX_OVERFLOW   (1UL << 5)
/*Receive character timeout (optional)*/
#define 	ARM_USART_EVENT_RX_TIMEOUT   (1UL << 6)
/*Break detected on receive.*/
#define 	ARM_USART_EVENT_RX_BREAK   (1UL << 7)
/*Framing error detected on receive.*/
#define 	ARM_USART_EVENT_RX_FRAMING_ERROR   (1UL << 8)
/*Parity error detected on receive.*/
#define 	ARM_USART_EVENT_RX_PARITY_ERROR   (1UL << 9)
/*CTS state changed (optional)*/
#define 	ARM_USART_EVENT_CTS   (1UL << 10)
/*DSR state changed (optional)*/
#define 	ARM_USART_EVENT_DSR   (1UL << 11)
/*DCD state changed (optional)*/
#define 	ARM_USART_EVENT_DCD   (1UL << 12)
/*RI state changed (optional)*/
#define 	ARM_USART_EVENT_RI   (1UL << 13)


/**
 * @brief UART mode control 
 * 
 */
/*UART (Asynchronous); arg = Baudrate.*/
#define 	ARM_USART_MODE_ASYNCHRONOUS   (0x01UL << ARM_USART_CONTROL_Pos)
/*Synchronous Master (generates clock signal); arg = Baudrate.*/
#define 	ARM_USART_MODE_SYNCHRONOUS_MASTER   (0x02UL << ARM_USART_CONTROL_Pos)
/*Synchronous Slave (external clock signal)*/
#define 	ARM_USART_MODE_SYNCHRONOUS_SLAVE   (0x03UL << ARM_USART_CONTROL_Pos)
/*UART Single-wire (half-duplex); arg = Baudrate.*/
#define 	ARM_USART_MODE_SINGLE_WIRE   (0x04UL << ARM_USART_CONTROL_Pos)
/*UART IrDA; arg = Baudrate.*/
#define 	ARM_USART_MODE_IRDA   (0x05UL << ARM_USART_CONTROL_Pos)
/*UART Smart Card; arg = Baudrate.*/
#define 	ARM_USART_MODE_SMART_CARD   (0x06UL << ARM_USART_CONTROL_Pos)

/**
 * @brief Specifies additional miscellaneous controls.
 * 
 */
/*Set default Transmit value (Synchronous Receive only); arg = value.*/
#define 	ARM_USART_SET_DEFAULT_TX_VALUE   (0x10UL << ARM_USART_CONTROL_Pos)
/*Set IrDA Pulse in ns; arg: 0=3/16 of bit period.*/
#define 	ARM_USART_SET_IRDA_PULSE   (0x11UL << ARM_USART_CONTROL_Pos)
/*Set Smart Card Guard Time; arg = number of bit periods.*/
#define 	ARM_USART_SET_SMART_CARD_GUARD_TIME   (0x12UL << ARM_USART_CONTROL_Pos)
/*Set Smart Card Clock in Hz; arg: 0=Clock not generated.*/
#define 	ARM_USART_SET_SMART_CARD_CLOCK   (0x13UL << ARM_USART_CONTROL_Pos)
/*Smart Card NACK generation; arg: 0=disabled, 1=enabled.*/
#define 	ARM_USART_CONTROL_SMART_CARD_NACK   (0x14UL << ARM_USART_CONTROL_Pos)
/*	Transmitter; arg: 0=disabled, 1=enabled.*/
#define 	ARM_USART_CONTROL_TX   (0x15UL << ARM_USART_CONTROL_Pos)
/*Receiver; arg: 0=disabled, 1=enabled*/
#define 	ARM_USART_CONTROL_RX   (0x16UL << ARM_USART_CONTROL_Pos)
/*Continuous Break transmission; arg: 0=disabled, 1=enabled.*/
#define 	ARM_USART_CONTROL_BREAK   (0x17UL << ARM_USART_CONTROL_Pos)
/*Abort ARM_USART_Send.*/
#define 	ARM_USART_ABORT_SEND   (0x18UL << ARM_USART_CONTROL_Pos)
/*Abort ARM_USART_Receive.*/
#define 	ARM_USART_ABORT_RECEIVE   (0x19UL << ARM_USART_CONTROL_Pos)
/*	Abort ARM_USART_Transfer.*/
#define 	ARM_USART_ABORT_TRANSFER   (0x1AUL << ARM_USART_CONTROL_Pos)

/**
 * @brief Defines the number of data bits
 * 
 */

#define 	ARM_USART_DATA_BITS_5   (5UL << ARM_USART_DATA_BITS_Pos)
#define 	ARM_USART_DATA_BITS_6   (6UL << ARM_USART_DATA_BITS_Pos)
#define 	ARM_USART_DATA_BITS_7   (7UL << ARM_USART_DATA_BITS_Pos)
#define 	ARM_USART_DATA_BITS_8   (0UL << ARM_USART_DATA_BITS_Pos)
#define 	ARM_USART_DATA_BITS_9   (1UL << ARM_USART_DATA_BITS_Pos)

/**
 * @brief Defines the parity bit
 * 
 */
/*No Parity (default)*/
#define 	ARM_USART_PARITY_NONE   (0UL << ARM_USART_PARITY_Pos)
/*Even Parity.*/
#define 	ARM_USART_PARITY_EVEN   (1UL << ARM_USART_PARITY_Pos)
/*Odd Parity.*/
#define 	ARM_USART_PARITY_ODD   (2UL << ARM_USART_PARITY_Pos)


/**
 * @brief Defines the number of stop bits.
 * 
 */
/*1 Stop bit (default)*/
#define 	ARM_USART_STOP_BITS_1   (0UL << ARM_USART_STOP_BITS_Pos)
/*2 Stop bits*/
#define 	ARM_USART_STOP_BITS_2   (1UL << ARM_USART_STOP_BITS_Pos)
/*1.5 Stop bits*/
#define 	ARM_USART_STOP_BITS_1_5   (2UL << ARM_USART_STOP_BITS_Pos)
/*0.5 Stop bits*/
#define 	ARM_USART_STOP_BITS_0_5   (3UL << ARM_USART_STOP_BITS_Pos)

/**
 * @brief Specifies RTS/CTS flow control
 * 
 */
/*No Flow Control (default)*/
#define 	ARM_USART_FLOW_CONTROL_NONE   (0UL << ARM_USART_FLOW_CONTROL_Pos)
/*RTS Flow Control.*/
#define 	ARM_USART_FLOW_CONTROL_RTS   (1UL << ARM_USART_FLOW_CONTROL_Pos)
/*CTS Flow Control.*/
#define 	ARM_USART_FLOW_CONTROL_CTS   (2UL << ARM_USART_FLOW_CONTROL_Pos)
/*RTS/CTS Flow Control.*/
#define 	ARM_USART_FLOW_CONTROL_RTS_CTS   (3UL << ARM_USART_FLOW_CONTROL_Pos)

/**
 * @brief Defines the clock polarity for the synchronous mode
 * 
 */

 /*CPOL = 0 (default)*/
#define 	ARM_USART_CPOL0   (0UL << ARM_USART_CPOL_Pos)
/*CPOL = 1.*/
#define 	ARM_USART_CPOL1   (1UL << ARM_USART_CPOL_Pos)

/**
 * @brief Defines the clock phase for the synchronous mode.
 * 
 */
/*CPHA = 0 (default)*/
#define 	ARM_USART_CPHA0   (0UL << ARM_USART_CPHA_Pos)
/*CPHA = 1.*/
#define 	ARM_USART_CPHA1   (1UL << ARM_USART_CPHA_Pos)


/**
 * @brief USART Device Driver Capabilities.
An USART driver can be implemented with different capabilities. The data fields of this structure encode the capabilities implemented by this driver.
 * 
 */
typedef struct ARM_USART_CAPABILITIES
{
    
    /*supports UART (Asynchronous) mode*/
    uint32_t	asynchronous: 1;
    /*supports Synchronous Master mode*/
    uint32_t	synchronous_master: 1;
    /*supports Synchronous Slave mode*/	
    uint32_t	synchronous_slave: 1;
    /*supports UART Single-wire mode*/	
    uint32_t	single_wire: 1;
    /*supports UART IrDA mode*/
    uint32_t	irda: 1;
    /*supports UART Smart Card mode*/
    uint32_t	smart_card: 1;
    /*Smart Card Clock generator available.*/
    uint32_t	smart_card_clock: 1;
    /*RTS Flow Control available.*/
    uint32_t	flow_control_rts: 1;
    /*CTS Flow Control available.*/
    uint32_t	flow_control_cts: 1;
    /*Transmit completed event: ARM_USART_EVENT_TX_COMPLETE.*/
    uint32_t	event_tx_complete: 1;
    /*Signal receive character timeout event: ARM_USART_EVENT_RX_TIMEOUT.*/	
    uint32_t	event_rx_timeout: 1;
    /*RTS Line: 0=not available, 1=available.*/
    uint32_t	rts: 1;
    /*CTS Line: 0=not available, 1=available.*/
    uint32_t	cts: 1;
    /*DTR Line: 0=not available, 1=available.*/
    uint32_t	dtr: 1;
    /*DSR Line: 0=not available, 1=available.*/	
    uint32_t	dsr: 1;
    /*DCD Line: 0=not available, 1=available.*/
    uint32_t	dcd: 1;
    /*RI Line: 0=not available, 1=available.*/
    uint32_t	ri: 1;
    /*Signal CTS change event: ARM_USART_EVENT_CTS*/
    uint32_t	event_cts: 1;
    /*Signal DSR change event: ARM_USART_EVENT_DSR.*/
    uint32_t	event_dsr: 1;
    /*Signal DCD change event: ARM_USART_EVENT_DCD.*/
    uint32_t	event_dcd: 1;
    /*1	Signal RI change event: ARM_USART_EVENT_RI.*/
    uint32_t	event_ri: 1;
    /*Reserved (must be zero)*/
    uint32_t	reserved: 11;

}ARM_USART_CAPABILITIES;


/**
 * @brief USART Status.
Structure with information about the status of the USART. The data fields encode busy flags and error flags.
 * 
 */;
typedef struct ARM_USART_STATUS
{
    /*Transmitter busy flag.*/
    uint32_t	tx_busy: 1;	
    /*Receiver busy flag.*/
    uint32_t	rx_busy: 1;	
    /*Transmit data underflow detected (cleared on start of next send operation)*/
    uint32_t	tx_underflow: 1;
    /*Receive data overflow detected (cleared on start of next receive operation)*/
    uint32_t	rx_overflow: 1;	
    /*Break detected on receive (cleared on start of next receive operation)*/
    uint32_t	rx_break: 1;
    /*Framing error detected on receive (cleared on start of next receive operation)*/
    uint32_t	rx_framing_error: 1;
    /*Parity error detected on receive (cleared on start of next receive operation)*/
    uint32_t	rx_parity_error: 1;	
    uint32_t	reserved: 25;
}ARM_USART_STATUS;

/**
 * @brief USART Modem Status.
Structure with information about the status of modem lines. The data fields encode states of modem status lines.
 * 
 */
typedef struct ARM_USART_MODEM_STATUS
{
    /*CTS state: 1=Active, 0=Inactive.*/
    uint32_t	cts: 1;
    /*	DSR state: 1=Active, 0=Inactive.*/
    uint32_t	dsr: 1;
    /*	DCD state: 1=Active, 0=Inactive.*/
    uint32_t	dcd: 1;
    /*	RI state: 1=Active, 0=Inactive.*/
    uint32_t	ri: 1;
    uint32_t	reserved: 28;
}ARM_USART_MODEM_STATUS;


typedef enum ARM_USART_MODEM_CONTROL
{
    /*Deactivate RTS.*/
    ARM_USART_RTS_CLEAR, 	
    /*Activate RTS.*/
    ARM_USART_RTS_SET, 	
    /*Deactivate DTR.*/
    ARM_USART_DTR_CLEAR, 	
    /*Activate DTR.*/
    ARM_USART_DTR_SET 	

}ARM_USART_MODEM_CONTROL;


/*Pointer to \ref ARM_USART_SignalEvent : Signal USART Event.*/
typedef void (*ARM_USART_SignalEvent_t) (uint32_t event);



/**
 * @brief Access structure of the USART Driver.
 * USART driver are accessed by function pointers exposed by this structure.
 */
typedef struct ARM_DRIVER_USART
{
    /*Pointer to ARM_USART_GetVersion : Get driver version.*/
    ARM_DRIVER_VERSION      (*GetVersion )(void);
    /*Pointer to ARM_USART_GetCapabilities : Get driver capabilities.*/
    ARM_USART_CAPABILITIES  (*GetCapabilities)(void);
    /*Pointer to ARM_USART_Initialize : Initialize USART Interface.*/
    int32_t  (*Initialize) (ARM_USART_SignalEvent_t cb_event);
    /*Pointer to ARM_USART_Uninitialize : De-initialize USART Interface.*/
    int32_t  (*Uninitialize )(void);
    /*Pointer to ARM_USART_PowerControl : Control USART Interface Power.*/
    int32_t  (*PowerControl )(ARM_POWER_STATE state);
    /*Pointer to ARM_USART_Send : Start sending data to USART transmitter.*/
    int32_t  (*Send )(const void *data, uint32_t num);
    /*Pointer to ARM_USART_Receive : Start receiving data from USART receiver.*/
    int32_t  (*Receive )(void *data, uint32_t num);
    /*Pointer to ARM_USART_Transfer : Start sending/receiving data to/from USART.*/
    int32_t  (*Transfer )(const void *data_out, void *data_in, uint32_t num);
    /*Pointer to ARM_USART_GetTxCount : Get transmitted data count.*/
    uint32_t (*GetTxCount )(void);
    /*Pointer to ARM_USART_GetRxCount : Get received data count.*/
    uint32_t (*GetRxCount )(void);
    /*Pointer to ARM_USART_Control : Control USART Interface.*/
    int32_t  (*Control )(uint32_t control, uint32_t arg);
    /*Pointer to ARM_USART_GetStatus : Get USART status.*/
    ARM_USART_STATUS    (*GetStatus )(void);
    /*Pointer to ARM_USART_SetModemControl : Set USART Modem Control line state.*/
    int32_t   (*SetModemControl )(ARM_USART_MODEM_CONTROL control);
    /*Pointer to ARM_USART_GetModemStatus : Get USART Modem Status lines state.*/
    ARM_USART_MODEM_STATUS  (*GetModemStatus )(void);

}ARM_DRIVER_USART;



#ifdef  __cplusplus
}
#endif


#endif
