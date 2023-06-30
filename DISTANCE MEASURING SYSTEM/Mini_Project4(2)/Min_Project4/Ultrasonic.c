/*----------------------------------------------------------------------------
 [file name]: Ultrasonic.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 17/10/2022
 [DESCRIPTION]: source file for the Ultrasonic driver
 -----------------------------------------------------------------------------*/
#include"Ultrasonic.h"
#include"ICU.h"
#include"GPIO.h"
#include"std_types.h"
#include"util/delay.h"
#include<avr/io.h>
	ICU_config config = {PRE_8, RISING_EDGE};

void Ultrasonic_init(void)
{
	ICU_init(&config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	setPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);
}

void Ultrasonic_Trigger(void)
{
	writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
//	_delay_ms(1);
}

uint16 high_time;

uint16 Ultrasonic_readDistance(void)
{
	uint16 distance = 0;
	/* supply a short 10uS pulse to the trigger input to start the ranging*/
	Ultrasonic_Trigger();
	/*calculate distance in CM*/
	distance = (uint16)(high_time/58.8);
	return distance;
}
