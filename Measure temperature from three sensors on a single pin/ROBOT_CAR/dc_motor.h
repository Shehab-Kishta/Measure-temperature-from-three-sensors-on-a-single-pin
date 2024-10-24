 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for the DC-Motor driver
 *
 * Author: Shehab Kishta
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#define MOTOR1_INPUT1	PD4
#define MOTOR1_INPUT2	PD5
#define MOTOR1_EN		PD3

#define MOTOR2_INPUT1	PD6
#define MOTOR2_INPUT2	PD7
#define MOTOR2_EN		PB1

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
	CAR_STOP,
	CAR_FORWARD,
	CAR_BACKWARD,
	CAR_LEFT,
	CAR_RIGHT
}Car_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initialize the DC Motor by:
 * 1. Setup the direction of the two motor pins as output by send the request to GPIO driver.
 * 2. Stop the motor at the beginning
 */
void DcMotors_Init(void);

/*
 * Description :
 * 1. Rotate  or Stop the motor according to the state input variable.
 * 2. Control the motor speed 0 --> 100% from its maximum speed by sending to PWM driver.
 */
void Car_Move(Car_State state);


#endif /* DC_MOTOR_H_ */
