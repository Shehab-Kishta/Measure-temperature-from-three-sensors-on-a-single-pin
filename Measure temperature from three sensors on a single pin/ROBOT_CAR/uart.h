/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Shehab Kishta
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define UART_BaudRate		 	uint32
#define Freq_CPU				16000000UL
#define returnByte_data			uint8
#define Tx						PD1
#define Rx						PD0
/*******************************************************************************
 *                         Configurations                                      *
 *******************************************************************************/

typedef enum
{
	FIVE,SIX,SEVEN,EIGHT
}UART_BitData;

typedef enum
{
	DISABLED,ENABLED_EVEN=2,ENABLED_ODD
}UART_Parity;

typedef enum
{
	ONE,TWO
}UART_StopBit;

typedef struct{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);


#endif /* UART_H_ */
