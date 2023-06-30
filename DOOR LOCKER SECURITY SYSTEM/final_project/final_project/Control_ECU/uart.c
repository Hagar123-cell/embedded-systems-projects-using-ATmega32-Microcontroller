/*
 * uart.c
 *
 *  Created on: Oct 21, 2022
 *      Author: OMR
 */

#include"uart.h"
#include<avr/io.h>
#include"std_types.h"
#include"common_macros.h"
void UART_init(const UART_ConfigType * Config_Ptr)
{
	//uint8 no_of_data_bits =
	uint16 UBRR_VALUE = 0;
	/*set U2X to double transfer rate for asynchronus comm*/
	UCSRA = (1<<U2X);
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * TXEN  = 1 Transmitter Enable
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN) | ((GET_BIT((Config_Ptr-> bit_data), 2))<<UCSZ2);
	/************************** UCSRC Description **************************
		 *URSEL = 1 to read UCSRC and not write to ubrrh
		 *UCSZ0 = 1 & UCSZ1 = 1 to enable 8 bits mode
		 ***********************************************************************/
	UCSRC = (GET_BIT((Config_Ptr-> bit_data), 0)<<UCSZ0) |(GET_BIT((Config_Ptr-> bit_data), 1)<<UCSZ1) | ((Config_Ptr -> parity) << UPM0) | ((Config_Ptr->stop_bit) << USBS) | (1<<URSEL);

	/* Calculate the UBRR register value */
	UBRR_VALUE = (uint16)(((F_CPU / ((Config_Ptr -> baud_rate) * 8UL))) - 1);

		/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
		UBRRH = UBRR_VALUE>>8;
		UBRRL = UBRR_VALUE;
}

void UART_sendByte(uint8 data)
{
	/*polling until data buffer is empty*/
	while(!(UCSRA &(1<<UDRE))){}
	UDR = data;
}
uint8 UART_recieveByte(void)
{
	/*polling until recieve complete*/
	while(!(UCSRA &(1<<RXC))){}
	return UDR;
}

void UART_sendString(const uint8* str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

void UART_recieveString(uint8 *recieved_str)
{
	uint8 i = 0;
	recieved_str[i] = UART_recieveByte();
	while(recieved_str[i] != '#')
	{
		i++;
		recieved_str[i] = UART_recieveByte();
	}
	recieved_str[i] = '\0';
}
