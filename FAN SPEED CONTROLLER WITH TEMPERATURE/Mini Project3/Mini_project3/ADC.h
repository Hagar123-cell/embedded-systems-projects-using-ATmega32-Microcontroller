/*----------------------------------------------------------------------------
 [file name]: ADC.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:header file for the AVR ADC driver
 -----------------------------------------------------------------------------*/
#ifndef ADC_H_
#define ADC_H_

#include"std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{AREF, AVCC, INTERNAL=3}ADC_ReferenceVolatge;

typedef enum
{PRE_1, PRE_2, PRE_4,PRE_8, PRE_16, PRE_32, PRE_64, PRE_148}ADC_Prescaler;

typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * DESCRIPTION:
 * INTIALIZE ADC WITH THE GIVEN CONFIGURATION
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * READ THE DIGITAL VALUE IN THE GIVEN CHANNEL
 */
uint16 ADC_readChannel(uint8 ch_num);
#endif /* ADC_H_ */
