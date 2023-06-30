/*----------------------------------------------------------------------------
 [file name]: PWM.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 10/10/2022
 [DESCRIPTION]:header file for the AVR PWM driver
 -----------------------------------------------------------------------------*/

#ifndef PWM_H_
#define PWM_H_
#include"std_types.h"
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


#endif /* PWM_H_ */
