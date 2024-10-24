/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the DC-Motor driver
 *
 * Author: Shehab Kishta
 *
 *******************************************************************************/

#include "dc_motor.h"
#include "uart.h"
#include "avr/io.h" /* To use the IO Ports Registers */

void DcMotors_Init(void)
{
	// Set motor pins as outputs
	DDRD |= (1 << MOTOR1_INPUT1) | (1 << MOTOR1_INPUT2) | (1 << MOTOR2_INPUT1) | (1 << MOTOR2_INPUT2) | (1<< MOTOR1_EN);
	DDRB |= (1 << MOTOR2_EN);
}

void Car_Move(Car_State state) {

	switch(state) {
	case CAR_STOP:
		// Stop the car by setting all motor pins to logic low
		PORTD &=~ (1 << MOTOR1_EN) ;
		PORTB &=~ (1 << MOTOR2_EN);
		PORTD &=~ (1 << MOTOR1_INPUT2) ;
		PORTD &=~ (1 << MOTOR2_INPUT1);
		PORTD &=~ (1<< MOTOR1_INPUT1);
		PORTD &=~ (1<< MOTOR2_INPUT2);
		break;

	case CAR_FORWARD:
		// Move the car forward by setting the appropriate motor pins to logic high
		PORTD |= (1 << MOTOR1_EN);
		PORTB |= (1 << MOTOR2_EN);
		PORTD |= (1 << MOTOR1_INPUT2);
		PORTD &=~ (1 << MOTOR1_INPUT1);
		PORTD |= (1 << MOTOR2_INPUT2);
		PORTD &=~ (1 << MOTOR2_INPUT1);
		UART_sendByte('F');
		break;

	case CAR_BACKWARD:
		// Move the car backward by setting the appropriate motor pins to logic high
		PORTD |= (1 << MOTOR1_EN);
		PORTB |= (1 << MOTOR2_EN);
		PORTD |= (1 << MOTOR1_INPUT1) | (1 << MOTOR2_INPUT1);
		PORTD &=~ (1 << MOTOR1_INPUT2);
		PORTD &=~ (1 << MOTOR2_INPUT2);
		UART_sendByte('B');
		break;

	case CAR_LEFT:
		// Turn the car left by setting the appropriate motor pins to logic high
		PORTD |= (1 << MOTOR1_EN);
		PORTB |= (1 << MOTOR2_EN);
		PORTD |= (1 <<MOTOR1_INPUT2) | (1 << MOTOR2_INPUT1);
		PORTD &=~ (1<<MOTOR1_INPUT1);
		PORTD &=~ (1<<MOTOR2_INPUT2);
		UART_sendByte('L');
		break;

	case CAR_RIGHT:
		// Turn the car right by setting the appropriate motor pins to logic high
		PORTD |= (1 << MOTOR1_EN);
		PORTB |= (1 << MOTOR2_EN);
		PORTD &=~ (1 << MOTOR1_INPUT2) ;
		PORTD &=~ (1 << MOTOR2_INPUT1);
		PORTD |= (1<< MOTOR1_INPUT1);
		PORTD |= (1<< MOTOR2_INPUT2);
		UART_sendByte('R');
		break;

	default:
		// Invalid state, stop the car just in case
		PORTD &=~ (1 << MOTOR1_EN) ;
		PORTB &=~ (1 << MOTOR2_EN);
		PORTD &=~ (1 << MOTOR1_INPUT2) ;
		PORTD &=~ (1 << MOTOR2_INPUT1);
		PORTD &=~ (1<< MOTOR1_INPUT1);
		PORTD &=~ (1<< MOTOR2_INPUT2);
		break;
	}
}
