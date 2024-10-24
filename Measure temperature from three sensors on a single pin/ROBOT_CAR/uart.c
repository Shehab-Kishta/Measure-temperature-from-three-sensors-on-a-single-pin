/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Shehab Kishta
 *
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device.
 */
void UART_init(const UART_ConfigType *Config_Ptr)
{
	// Bluetooth pins as output and input
	DDRD |= ( 1 << Tx);
	DDRD &=~ (1 <<Rx);

	uint16 ubrr_value = 0;

	/************************** UCSR0B Description **************************
	 * RXEN  = 1 Receiver Enable
	 * TXEN  = 1 Transmitter Enable
	 ***********************************************************************/
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

	/*
	 * the UCSR0C register is first ANDed with 0xCF to clear the UPM01 and UPM00 bits, while preserving the other bits in the register.
	 * Then, the value of Config_Ptr->parity is left-shifted by 4 and ORed with the UCSR0C register.
	 * This sets the UPM01 and UPM00 bits to the desired value based on the value of Config_Ptr->parity.
	 * The value of Config_Ptr->parity should be one of the following values:
	 * 0: No parity
	 * 1: Even parity
	 * 2: Odd parity
	 */
	UCSR0C = ( UCSR0C & 0xCF ) | ( (Config_Ptr->parity) << 4);

	/*
	 * Configuring the number of stop bits:
	 * By clearing the USBS0 bit in the register by ANDing it with the complement of (1<<USBS0),
	 * and then setting the bit to the desired value by ORing it with ((Config_Ptr->stop_bit) << USBS0).
	 * The value of Config_Ptr->stop_bit should be either 0 or 1.
	 */
	UCSR0C = (UCSR0C & ~(1<<USBS0)) | ((Config_Ptr->stop_bit) << USBS0);

	/*
	 * Configuring the data frame size:
	 * By clearing these two bits by ANDing the register with the complement of (3<<UCSZ00),
	 * and then setting the bits to the desired value by ORing it with (((Config_Ptr->bit_data) & 0x03) << UCSZ00).
	 * The value of Config_Ptr->bit_data should be a number between 5 and 8.
	 */
	UCSR0C = (UCSR0C & ~(3<<UCSZ00)) | (((Config_Ptr->bit_data) & 0x03) << UCSZ00);

	/*
	 * configuring the optional ninth data bit:
	 *  By clearing the UCSZ02 bit by ANDing the register with the complement of (1<<UCSZ02),
	 *  and then setting the bit to the desired value by ORing it with (((Config_Ptr->bit_data) & 0x04) << UCSZ02).
	 *  If Config_Ptr->bit_data is set to 9, then the ninth data bit will be transmitted, otherwise it will be ignored.
	 */
	UCSR0B = (UCSR0B & ~(1<<UCSZ02)) | (((Config_Ptr->bit_data) & 0x04) << UCSZ02);

	ubrr_value = (uint16)((Freq_CPU/(16*(Config_Ptr->baud_rate))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH */
	UBRR0H = ubrr_value >> 8;
	UBRR0L = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSR0A,UDRE0)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR0 = data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSR0A,RXC0)){}

	/*
	 * Read the received data from the Rx buffer (UDR0)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR0;
}

