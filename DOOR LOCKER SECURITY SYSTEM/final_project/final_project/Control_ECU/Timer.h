/*
 * Timer1.h
 *
 *  Created on: Nov 2, 2022
 *      Author: OMR
 */

#ifndef TIMER_H_
#define TIMER_H_

#include"std_types.h"

/******************************Timer0******************************************/
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
void PWM_Timer0_Start(uint8 duty_cycle);



/******************************Timer1******************************************/

/*******************************************************************************
                           types definitions
 ******************************************************************************/
typedef enum
{pre_1 = 1, pre_8, pre_64, pre_256, pre_1024}Timer1_Prescaler;

typedef enum
{normal, compare}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
                            functions prototypes
 ******************************************************************************/
/*
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Function to disable the Timer1
 */
void Timer1_deInit(void);

/*
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER_H_ */
