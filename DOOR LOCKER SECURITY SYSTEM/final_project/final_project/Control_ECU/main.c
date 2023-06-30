/*
 * main.c
 *
 *  Created on: Nov 5, 2022
 *      Author: OMR
 */

#include"uart.h"
#include"i2c.h"
#include"external_eeprom.h"
#include"std_types.h"
#include"DC_MOTOR.h"
#include"util/delay.h"

int main(void)
{
	DcMotor_Init();
	UART_ConfigType config = {five_bits, no_parity, one_bit, 9600};
	UART_init(&config);

	while(1)
	{
		UART_sendByte(ready);

		uint8 pass1[5];
		uint8 pass2[5];
		uint8 flag = TRUE;
		UART_recieveString(pass1);
		UART_recieveString(pass2);
		for(uint8 i = 0; i<5; i++)
		{
			if(pass1[i] != pass2[i])
			{
				UART_sendByte(un_matched);
				flag = FALSE;
				break;
			}
		}

		TWI_ConfigType twi_config = {0x01, F_400k};
		TWI_init(&twi_config);
		uint8 add = 0x1;
		if(flag == TRUE)
		{
			for(uint8 i=0; i<5; i++)
			{
				EEPROM_writeByte(add, pass1[i]);
				add++;
			}
		}
		/*********** + or - **************/
		while(UART_recieveByte() != ready_again){}
		uint8 pass[5], original_pass[5];
		UART_recieveString(pass);
		uint8 add_repeated = 0x1;
		uint8 flag2 = TRUE;
		for(uint8 i = 0; i<5; i++)
		{
			if(pass[i] != EEPROM_readByte(add_repeated, original_pass))
			{
				UART_sendByte(un_matched);
				flag2 = FALSE;
				break;
			}
			add_repeated++;
		}

		if(flag2 == TRUE)
		{
			UART_sendByte(matched);
			DcMotor_Rotate(clkWise);
			/*lccccccd*/
			_delay_ms(15000);
			DcMotor_Rotate(stop);
			_delay_ms(3000);
			DcMotor_Rotate(antiClkWise);
			_delay_ms(15000);
		}
	}
}
