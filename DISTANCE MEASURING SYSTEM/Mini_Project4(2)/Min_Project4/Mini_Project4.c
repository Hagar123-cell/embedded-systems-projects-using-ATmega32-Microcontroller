/*----------------------------------------------------------------------------
 [file name]: main.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 17/10/2022
 [DESCRIPTION]: source file for the main function
 -----------------------------------------------------------------------------*/
#include"LCD.h"
#include"ICU.h"
#include"Ultrasonic.h"
#include<avr/io.h>
extern uint16 high_time = 0;
uint8 count = 0;
void Ultrasonic_edgeProcessing(void)
{
	count++;
	if(count == 1)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING_EDGE);
	}
	else if(count == 2)
	{
		high_time = ICU_getInterruptCaptureValue();
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING_EDGE);
		count = 0;
	}
}
int main(void)
{
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	Ultrasonic_init();
	Ultrasonic_Trigger();
	LCD_init();
	LCD_displayString(" Distance =   cm");

	uint16 dist = 0;
	while(1)
	{
		if(count == 2)
		{
			count = 0;

			dist = Ultrasonic_readDistance();

			LCD_moveCursor(0,12);
			if(dist >= 100)
			{
				LCD_intgerToString(dist);
			}
			else
			{
				LCD_intgerToString(dist);
				/* In case the digital value is two or one digits print space in the next digit place */
				LCD_displayCharacter(' ');
			}

		}

	}

}
