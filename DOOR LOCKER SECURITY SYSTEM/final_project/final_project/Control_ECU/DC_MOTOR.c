/*----------------------------------------------------------------------------
 [file name]: DC_MOTOR.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:source file for the AVR DC_MOTOR driver
 -----------------------------------------------------------------------------*/
#include <avr/io.h>
#include"DC_MOTOR.h"
#include"GPIO.h"
#include"common_macros.h"
#define Timer0
#include"Timer.h"
void DcMotor_Init(void)
{
	/*SET IN1 & IN2 FOR THE DC_MOTOR AS OUTPUT*/
	setPinDirection(IN1_PORT_ID, IN1_PIN_ID, PIN_OUTPUT);
	setPinDirection(IN2_PORT_ID, IN2_PIN_ID, PIN_OUTPUT);

	/*stop the motor initialy*/
	CLEAR_BIT(PORTB, IN1_PIN_ID);
	CLEAR_BIT(PORTB, IN1_PIN_ID);

}

void DcMotor_Rotate(DcMotor_State state)
{
	/*adjust the state of the rotation of motor(clkwise/ anti clkwise/ stop)*/
	PORTB = (PORTB & 0xFC) | state;

	/*send the required speed to pwm to generate the wave on the enable pin of the motor*/
	PWM_Timer0_Start(100);
}
