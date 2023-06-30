/*----------------------------------------------------------------------------
 [file name]: PWM.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:source file for the AVR PWM driver
 -----------------------------------------------------------------------------*/

#include"PWM.h"
#include"GPIO.h"
#include"avr/io.h"
/*
Description:
 The function responsible for trigger the Timer0 with the PWM Mode.
 Setup the PWM mode with Non-Inverting.
 Setup the prescaler with F_CPU/8.
 Setup the compare value based on the required input duty cycle
 Setup the direction for OC0 as output pin through the GPIO driver.
 The generated PWM signal frequency will be 500Hz to control the DC Motor speed.

 Inputs:
 duty_cycle: The required duty cycle percentage of the generated PWM signal. Its value should be from 0 → 100

 Return: Non
*/
void PWM_Timer0_Start(uint8 duty_cycle)
{
	/*SET INITIAL COUNTING VALUE*/
		TCNT0 = 0;

	/*
	 * SET COM01 TO WORK WITH NON INVERING MODE
	 * SET WGM01 & WGM00 TO SET TIMER0 ON FAST PWM MODE
	 * SET CS01 TO HAVE PRESCALER -> 8
	 */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);

	/*SET THE COMPARE VALUE ACCORDING TO THE DUTY CYCLE*/
	OCR0 = (uint8)(((uint32)duty_cycle*255)/100);

	/*SET PB3/OC0 AS OUTPUT TO GENERATE PWM ON*/
	setPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
}
