/******************************************************************************
 *
 * File Name: main.c
 *
 * Description: Source file for the ROBOT CAR
 *
 * Author: Shehab Kishta
 *
 *******************************************************************************/
#include"avr\io.h"
#include"std_types.h"
#include<util/delay.h>
#include"uart.h"
#include"dc_motor.h"
#include"twi.h"
#include"lcd.h"
#include "lm35_sensor.h"
#include "adc.h"
/************************************************************************************************
 *                                GLOBAL VARIABLES                                              *
 ************************************************************************************************/

UART_ConfigType UART_configuration = {EIGHT, DISABLED, ONE, 9600};
ADC_ConfigType ADC_Config = {INTERNAL_VOLT, F_CPU_16};

int main(void)
{
	uint8 direction;
	uint8 Temp = 0;

	UART_init(&UART_configuration);
	ADC_init(&ADC_Config);
	DcMotors_Init();
	TWI_init();
	LCD_init();
	SREG  |= (1<<7);
	DDRC &= (1<<PC2);

	LCD_clearScreen();
	LCD_displayString("T1=   C");
	_delay_ms(100);
	LCD_moveCursor(0,8);
	LCD_displayString("T2=   C");
	/* Display this string "Temp =   C" only once on LCD at the second row*/
	LCD_moveCursor(1,0);
	LCD_displayString("T3=   C");
	_delay_ms(100);

	while(1){
		PORTB &= ~(1 << PB5);
		PORTB &= ~(1 << PB4);
		/* Get the temperature value */
		Temp = LM35_getTemperature();
		LCD_moveCursor(0,3);
		if(Temp >= 100)
		{
			LCD_intgerToString(Temp);
		}else
		{
			LCD_displayCharacter(' ');
			LCD_intgerToString(Temp);
		}

		_delay_ms(100);
		PORTB |= (1 << PB5);
		PORTB &= ~(1 << PB4);
		/* Get the temperature value */
		Temp = LM35_getTemperature();
		LCD_moveCursor(0,11);
		if(Temp >= 100)
		{
			LCD_intgerToString(Temp);
		}else
		{
			LCD_displayCharacter(' ');
			LCD_intgerToString(Temp);
		}
		_delay_ms(100);
		PORTB |= (1 << PB4);
		PORTB &= ~(1 << PB5);
		/* Get the temperature value */
		Temp = LM35_getTemperature();
		LCD_moveCursor(1,3);
		if(Temp >= 100)
		{
			LCD_intgerToString(Temp);
		}else
		{
			LCD_displayCharacter(' ');
			LCD_intgerToString(Temp);
		}
		_delay_ms(100);
		if (UCSR0A & (1 << RXC0)) {
			direction = UART_recieveByte();
			Car_Move(CAR_STOP);
			switch(direction){
			case 'F': // move forward
				Car_Move(CAR_FORWARD); // move the car forward at the specified speed
				_delay_ms(10);
				break;

			case 'B': // move backward
				Car_Move(CAR_BACKWARD); // move the car backward at the specified speed
				_delay_ms(10);
				break;

			case 'R': // turn right
				Car_Move(CAR_RIGHT); // turn the car right at the specified speed
				_delay_ms(10);
				break;

			case 'L': // turn left
				Car_Move(CAR_LEFT); // turn the car left at the specified speed
				_delay_ms(10);
				break;

			default: // stop the car
				Car_Move(CAR_STOP); // stop the car
				_delay_ms(10);
				break;
			}
		}
	}
}
