/*----------------------------------------------------------------------------
 [file name]: GPIO.h
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 9/10/2022
 [DESCRIPTION]:header file for the AVR GPIO driver
 -----------------------------------------------------------------------------*/

#ifndef GPIO_H_
#define GPIO_H_

#include"std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS            4
#define NUM_OF_PINS_PER_PORT    8

#define PORTA_ID                0
#define PORTB_ID                1
#define PORTC_ID                2
#define PORTD_ID                3

#define PIN0_ID                 0
#define PIN1_ID                 1
#define PIN2_ID                 2
#define PIN3_ID                 3
#define PIN4_ID                 4
#define PIN5_ID                 5
#define PIN6_ID                 6
#define PIN7_ID                 7
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void setPinDirection(uint8 PORT_ID,uint8 PIN_ID, GPIO_PinDirectionType direction);
void setPortDirection(uint8 PORT_ID, GPIO_PortDirectionType direction);

uint8 readPin(uint8 PORT_ID, uint8 PIN_ID);
void writePin(uint8 PORT_ID, uint8 PIN_ID, uint8 value );

uint32 readPort(uint8 PORT_ID);
void writePort(uint8 PORT_ID, uint32 value);


#endif /* GPIO_H_ */
