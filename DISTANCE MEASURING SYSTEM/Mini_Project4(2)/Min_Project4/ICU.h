/*----------------------------------------------------------------------------
 [file name]: ICU.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 17/10/2022
 [DESCRIPTION]: source file for the AVR ICU driver
 -----------------------------------------------------------------------------*/

#ifndef ICU_H_
#define ICU_H_

#include"std_types.h"
/*************************************
                                      types declarations
 ************************************/
typedef enum
{NO_CLK, PRE_1, PRE_8, PRE_64, PRE_256, PRE_1024}ICU_CLK;
typedef enum
{FALLING_EDGE, RISING_EDGE}CAPTURE_EVENT;
typedef struct
{
	ICU_CLK clk;
	CAPTURE_EVENT event;
}ICU_config;

/*************************************
                                      functions prototypes
 ************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(ICU_config* config);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void (*ptr2call_back_fn)(void));

/*
 * Description: Function to set the required edge detection.
 */
void Icu_setEdgeDetectionType(const CAPTURE_EVENT a_edgeType);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInterruptCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void Icu_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void Icu_DeInit(void);

#endif /* ICU_H_ */
