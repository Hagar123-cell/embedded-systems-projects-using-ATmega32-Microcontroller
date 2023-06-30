/*----------------------------------------------------------------------------
 [file name]: AUTO_SPEED_CONTROLLER.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 11/10/2022
 [DESCRIPTION]:source file for main function
 -----------------------------------------------------------------------------*/
#include"DC_MOTOR.h"
#include"LCD.h"
#include"TEMP_SENSOR.h"
#include"ADC.h"
int main(void)
{
	DcMotor_Init();
	ADC_ConfigType adc_config = {INTERNAL, PRE_8};
	ADC_init(&adc_config);
	LCD_init();
	while(1)
	{

		if(LM35_getTemperature() < 30)
		{
			DcMotor_Rotate(stop, 0); /*stop the fan*/
			LCD_displayStringRowColumn(0, 2, "FAN IS OFF");
		}
		else if((LM35_getTemperature() >= 30) && (LM35_getTemperature() < 60))
		{
			DcMotor_Rotate(clkWise, 25); /*turn on the fan with 25% of its max. speed*/
			LCD_displayStringRowColumn(0, 2, "FAN IS ON ");

		}
		else if((LM35_getTemperature() >= 60) && (LM35_getTemperature() < 90))
		{
			DcMotor_Rotate(clkWise, 50); /*turn on the fan with 50% of its max. speed*/
			LCD_displayStringRowColumn(0, 2, "FAN IS ON ");
		}
		else if((LM35_getTemperature() >= 90) && (LM35_getTemperature() < 120))
		{
			DcMotor_Rotate(clkWise, 75); /*turn on the fan with 75% of its max. speed*/
			LCD_displayStringRowColumn(0, 2, "FAN IS ON ");
		}
		else if(LM35_getTemperature() >= 120)
		{
			DcMotor_Rotate(clkWise, 100); /*turn on the fan with 100% of its max. speed*/
			LCD_displayStringRowColumn(0, 2, "FAN IS ON ");
		}
		LCD_displayStringRowColumn(1, 2, "Temp = ");
		LCD_intgerToString(LM35_getTemperature());
		LCD_displayCharacter('c');
	}
}
