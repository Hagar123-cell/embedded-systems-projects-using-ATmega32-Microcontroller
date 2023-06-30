/*
 * keypad.h
 *
 *  Created on: Oct 14, 2022
 *      Author: OMR
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include"std_types.h"

#define KEYPAD_BUTTON_PRESSED  LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED  LOGIC_HIGH

#define NO_OF_ROWS 4
#define NO_OF_COLS 4

#define KEYPAD_ROW_PORT_ID                PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID

#define KEYPAD_COL_PORT_ID                PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
