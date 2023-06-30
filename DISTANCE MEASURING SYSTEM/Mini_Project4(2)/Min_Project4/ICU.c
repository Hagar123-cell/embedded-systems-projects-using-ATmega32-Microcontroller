/*----------------------------------------------------------------------------
 [file name]: ICU.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 17/10/2022
 [DESCRIPTION]: source file for the AVR ICU driver
 -----------------------------------------------------------------------------*/

#include"ICU.h"
#include<avr/io.h>

/***************************
 *                           Global Variables                                  *
 ***************************/
static volatile void(*g_ICU_ptr2call_back_fn)(void);

/***************************
 *                       Interrupt Service Routines                            *
 ***************************/
ISR(TIMER1_CAPT_vect)
{
	/* Call the Call Back function in the ultrasonic after the edge is detected */
	if(g_ICU_ptr2call_back_fn != NULL_PTR)
	(*g_ICU_ptr2call_back_fn)();
}

/***************************
 *                      Functions Definitions                                  *
 ***************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(ICU_config* config)
{
	/* Configure ICP1/PD6 as i/p pin */
	DDRD &= ~(1<<PD6);

	/* Timer1 always operates in Normal Mode */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*
	 * set ICES1 to trigger capture with rising edge
	 * set CS11 to have 8 prescaler
	 */
	TCCR1B = (TCCR1B & 0xF8) | (config -> clk);
	TCCR1B = (TCCR1B & 0xBF) | ((config->event)<<6);

	/*set initial timer value*/
	TCNT1 = 0;

	/* Initial Value for the input capture register */
	ICR1 = 0;

	/*enable input capture interrupt*/
	TIMSK |= (1<<TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void (*ptr2call_back_fn)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_ICU_ptr2call_back_fn = ptr2call_back_fn;
}

/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(const CAPTURE_EVENT a_edgeType)
{
	/*
	 * insert the required edge type in ICES1 bit in TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInterruptCaptureValue(void)
{
	return ICR1;
}

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}


/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
