/*----------------------------------------------------------------------------
 [file name]: TEMP_SENSOR.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:header file for the AVR TEMP_SENSOR driver
 -----------------------------------------------------------------------------*/
#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include"std_types.h"
/*******************************************************************************
 *                              definitions                                    *
 *******************************************************************************/
#define MAX_TEMP 150
#define REF_VOLT 2.65
#define LM35_MAX_VOLT 1.5
#define MAX_DIGITAL_VALUE 1023

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
uint8 LM35_getTemperature(void);

#endif /* TEMP_SENSOR_H_ */
