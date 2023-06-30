/*
 * main.c
 *
 *  Created on: Nov 5, 2022
 *      Author: OMR
 */


#include"LCD.h"
#include"keypad.h"
#include"uart.h"
#include"util/delay.h"

void create_password(void)
{
	do
	{
		LCD_displayString("plz enter pass:");
		uint8 pass1[5];
		/*move cursor to second line*/
		LCD_moveCursor(1, 0);
		/*take password when user press enter"="*/

			for(uint8 i=0; i<5; i++)
			{
				pass1[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(1000);
			}
			while(KEYPAD_getPressedKey() != '='){}
			_delay_ms(1000);


		LCD_clearScreen();
		LCD_moveCursor(0, 0);
		LCD_displayString("plz re_enter the same pass:");
		uint8 pass2[5];
		/*move cursor to second line*/
		LCD_moveCursor(1, 10);
		/*take password when user press enter"="*/
		while(KEYPAD_getPressedKey() != '=')
		{
			for(uint8 i=0; i<5; i++)
			{
				pass2[i] = KEYPAD_getPressedKey();
				LCD_displayCharacter('*');
				_delay_ms(500);
			}
		}
		while(UART_recieveByte() != ready){}
		UART_sendString(pass1);
		UART_sendString(pass2);
		//	_delay_ms(0.5);
	}while(UART_recieveByte() == un_matched);
}

void send_pass_to_check(void)
{
	uint8 pass[5];
	LCD_clearScreen();
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1, 0);
	/*take password when user press enter"="*/
	while(KEYPAD_getPressedKey() != '=')
	{
		for(uint8 i=0; i<5; i++)
		{
			pass[i] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
			_delay_ms(500);
		}
	}
	UART_sendByte(ready_again);
	//_delay_ms(0.1);
	/*send pass to control_ECU to check it*/
	UART_sendString(pass);
}
int main(void)
{
	LCD_init();

	UART_ConfigType config = {five_bits, no_parity, one_bit, 9600};
	UART_init(&config);

	create_password();
	/*when passwords match*/
	LCD_clearScreen();
	LCD_displayString("+ : Open Door");
	/*move cursor to second line*/
	LCD_moveCursor(1, 0);
	LCD_displayString("- : Change Pass");
	if(KEYPAD_getPressedKey() == '+')
	{
		send_pass_to_check();
		while(UART_recieveByte() != un_matched && UART_recieveByte() != matched){}
		if(UART_recieveByte() == un_matched)
		{
			send_pass_to_check();
		}
		else if(UART_recieveByte() == matched)
		{
		}
	}
	else if(KEYPAD_getPressedKey() == '-')
	{
		send_pass_to_check();
		while(UART_recieveByte() != un_matched && UART_recieveByte() != matched){}
		if(UART_recieveByte() == un_matched)
		{

		}
		else if(UART_recieveByte() == matched)
		{
			create_password();
		}
	}

}
