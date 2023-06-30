/*----------------------------------------------------------------------------
 [file name]: TEMP_SENSOR.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:source file for the AVR TEMP_SENSOR driver
 -----------------------------------------------------------------------------*/
#include"TEMP_SENSOR.h"
#include"ADC.h"
uint8 LM35_getTemperature(void)
{
	uint16 adc_value = ADC_readChannel(2);
	uint8 temp = (uint8)(((uint32)adc_value * MAX_TEMP * REF_VOLT)/(LM35_MAX_VOLT * MAX_DIGITAL_VALUE));
	return temp;
}
