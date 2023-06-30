/*
 * uart.h
 *
 *  Created on: Oct 21, 2022
 *      Author: OMR
 */

#ifndef UART_H_
#define UART_H_

#include"std_types.h"

#define UART_BaudRate uint32
#define ready (uint8)0x12
#define un_matched (uint8)0x44
#define matched (uint8)0x66
#define ready_again (uint8)0x55


typedef enum
{five_bits, six_bits, seven_bits, eight_bits, nine_bits = 7}UART_BitData;

typedef enum
{no_parity, even_parity = 2, odd_parity}UART_Parity;

typedef enum
{one_bit, two_bits}UART_StopBit;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;

void UART_init(const UART_ConfigType * Config_Ptr);

void UART_sendByte(uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8* str);

void UART_recieveString(uint8 *recieved_str);

#endif /* UART_H_ */
