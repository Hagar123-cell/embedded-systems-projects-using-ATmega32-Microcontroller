/*----------------------------------------------------------------------------
 [file name]: ADC.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:source file for the AVR ADC driver
 -----------------------------------------------------------------------------*/
#include"ADC.h"
#include<avr/io.h>
#include"common_macros.h"
void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADJUST REFRENCE VOLT & SELECT CHANNEL0 TO TAKE ANALOG VALUE FROM*/
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr ->ref_volt)<<6);

	/*SELECT PRESCALER AND ENABLE ADC*/
	ADCSRA = ((ADCSRA & (0xF8)) | (Config_Ptr -> prescaler)) | (1<<ADEN);
}

uint16 ADC_readChannel(uint8 ch_num)
{
	/* SELECT CH_NUM*/
	ADMUX |= (ADMUX & 0xE0) | ch_num;

	/*START CONVERSION*/
	ADCSRA |= (1<<ADSC);

	/*POLLING TILL CONVERSION IS COMPLETE*/
	while(ADIF == 0);

	/*CLEAR ADIF FLAG*/
	CLEAR_BIT(ADCSRA, ADIF);

	return ADC;
}
