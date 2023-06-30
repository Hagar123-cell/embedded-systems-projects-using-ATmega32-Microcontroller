/*
 * Timer1.c
 *
 *  Created on: Nov 2, 2022
 *      Author: OMR
 */

/*******************************************************************************
                            includes
 ******************************************************************************/
#include "Timer.h"
#include<avr/io.h>

#include"GPIO.h"

/*******************************************************************************
                            functions
 ******************************************************************************/
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


#include<AVR/interrupt.h>
/*******************************************************************************
                            global variables
 ******************************************************************************/
static void(*g_timer1_call_back_ptr)(void) = NULL_PTR;

/*******************************************************************************
                            ISRs
 ******************************************************************************/
ISR(TIMER1_OVF_vect)
{
	if(g_timer1_call_back_ptr != NULL_PTR)
	{
		(*g_timer1_call_back_ptr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_timer1_call_back_ptr != NULL_PTR)
	{
		(*g_timer1_call_back_ptr)();
	}
}
/*******************************************************************************
                            functions
 ******************************************************************************/
/*
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/*set initial counting value*/
	TCNT1 = Config_Ptr -> initial_value;

	if(Config_Ptr -> mode == normal)
	{

		/* set FOC1A & FOC1B indicates non-pwm mode*/
		TCCR1A = (1<<FOC1B) | (1<<FOC1A);

		/* set ICNC1 to cancel ICU*/
		TCCR1B = (1<<ICNC1) | (Config_Ptr -> prescaler);

		/*  Overflow Interrupt Enable*/
		TIMSK |= (1<<TOIE1);
	}
	else if(Config_Ptr -> mode == compare)
	{

		/* set FOC1A & FOC1B indicates non-pwm mode*/

		TCCR1A = (1<<FOC1B) | (1<<FOC1A);

		/*
		 * set ICNC1 to cancel ICU
		 * set WGM12 to select CTC mode
		 */
		TCCR1B = (1<<ICNC1) | (1<<WGM12) | (Config_Ptr -> prescaler);

		/*set the compare value*/
		OCR1A = Config_Ptr -> compare_value;

		/* Output Compare A Match Interrupt Enable*/
		TIMSK |= (1<<OCIE1A);
	}
}

/*
 * Function to disable the Timer1
 */
void Timer1_deInit(void)
{
	/*clear CS10 &  CS11 &  CS12 to stop timer*/
	TCCR1B = 0;
}

/*
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_timer1_call_back_ptr = a_ptr;
}
