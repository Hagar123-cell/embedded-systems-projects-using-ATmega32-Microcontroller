/*----------------------------------------------------------------------------
 [file name]: Ultrasonic.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 17/10/2022
 [DESCRIPTION]: header file for the Ultrasonic driver
 -----------------------------------------------------------------------------*/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include"std_types.h"
/*************************************
                                         definitions
 *************************************/
#define TRIGGER_PORT_ID  PORTB_ID
#define TRIGGER_PIN_ID   PIN5_ID

/*************************************
                                         functions prototypes
 *************************************/
void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

void Ultrasonic_edgeProcessing(void);

uint16 Ultrasonic_readDistance(void);
#endif /* ULTRASONIC_H_ */
