/*
 * keypad.c
 *
 *  Created on: Oct 14, 2022
 *      Author: OMR
 */


#include"keypad.h"
#include"gpio.h"

#ifndef standard_keypad

#if (NO_OF_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (NO_OF_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif /* STANDARD_KEYPAD */
uint8 KEYPAD_getPressedKey(void)
{
	setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, PIN_INPUT);
	setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+1, PIN_INPUT);
	setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+2, PIN_INPUT);
	setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+3, PIN_INPUT);
	setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
	setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1, PIN_INPUT);
	setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2, PIN_INPUT);
#if (NO_OF_COLS == 4)
	setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3, PIN_INPUT);
#endif
	uint8 row, col;
	while(1)
	{
		for(row = 0; row<NO_OF_ROWS; row++)
		{
			setPinDirection(KEYPAD_ROW_PORT_ID, row, PIN_OUTPUT);
			writePin(KEYPAD_ROW_PORT_ID, row, KEYPAD_BUTTON_PRESSED);

			for(col = 0; col<NO_OF_COLS;col++)
			{
				if(!(readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+col)))//pressed
				{
#ifdef standard_keypad
					return ((row*NO_OF_COLS)+col+1);
#elif (NO_OF_COLS == 4)
					return KEYPAD_4x4_adjustKeyNumber((row*NO_OF_COLS)+col+1);
#elif(NO_OF_COLS == 3)
					return KEYPAD_4x3_adjustKeyNumber((row*NO_OF_COLS)+col+1);
#endif
				}
			}
			setPinDirection(KEYPAD_ROW_PORT_ID, row, PIN_INPUT);
		}
	}
}
#ifndef standard_keypad

#if (NO_OF_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 10: keypad_button = '*'; // ASCII Code of *
	break;
	case 11: keypad_button = 0;
	break;
	case 12: keypad_button = '#'; // ASCII Code of #
	break;
	default: keypad_button = button_number;
	break;
	}
	return keypad_button;
}

#elif (NO_OF_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 1: keypad_button = 7;
	break;
	case 2: keypad_button = 8;
	break;
	case 3: keypad_button = 9;
	break;
	case 4: keypad_button = '%'; // ASCII Code of %
	break;
	case 5: keypad_button = 4;
	break;
	case 6: keypad_button = 5;
	break;
	case 7: keypad_button = 6;
	break;
	case 8: keypad_button = '*'; /* ASCII Code of '*' */
	break;
	case 9: keypad_button = 1;
	break;
	case 10: keypad_button = 2;
	break;
	case 11: keypad_button = 3;
	break;
	case 12: keypad_button = '-'; /* ASCII Code of '-' */
	break;
	case 13: keypad_button = 13;  /* ASCII of Enter */
	break;
	case 14: keypad_button = 0;
	break;
	case 15: keypad_button = '='; /* ASCII Code of '=' */
	break;
	case 16: keypad_button = '+'; /* ASCII Code of '+' */
	break;
	default: keypad_button = button_number;
	break;
	}
	return keypad_button;
}
#endif
#endif /*standard_keypad*/
