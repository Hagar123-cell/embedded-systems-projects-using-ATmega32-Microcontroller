/*----------------------------------------------------------------------------
 [file name]: GPIO.c
 [AUTHOR]: Hagar Ahmed
 [DATE CREATED]: 9/10/2022
 [DESCRIPTION]: source file for the AVR GPIO driver
 -----------------------------------------------------------------------------*/
#include"GPIO.h"
#include"std_types.h"
#include"common_macros.h"
#include <avr/io.h>

/*
 * set the direction of the given pin (input / output)
 */
void setPinDirection(uint8 PORT_ID,uint8 PIN_ID, GPIO_PinDirectionType direction)
{
	if(PORT_ID >= NUM_OF_PORTS || PIN_ID >= NUM_OF_PINS_PER_PORT )
	{
		/*do nothing*/
	}
	else
	{
		switch(PORT_ID)
		{
		case PORTA_ID:
			if(direction == PIN_INPUT)
				CLEAR_BIT(DDRA, PIN_ID);
			else
				SET_BIT(DDRA, PIN_ID);
			break;
		case PORTB_ID:
			if(direction == PIN_INPUT)
				CLEAR_BIT(DDRB, PIN_ID);
			else
				SET_BIT(DDRB, PIN_ID);
			break;
		case PORTC_ID:
			if(direction == PIN_INPUT)
				CLEAR_BIT(DDRC, PIN_ID);
			else
				SET_BIT(DDRC, PIN_ID);
			break;
		case PORTD_ID:
			if(direction == PIN_INPUT)
				CLEAR_BIT(DDRD, PIN_ID);
			else
				SET_BIT(DDRD, PIN_ID);
			break;
		}
	}
}

/*
 * set the direction of the given port (input / output)
 */
void setPortDirection(uint8 PORT_ID, GPIO_PortDirectionType direction)
{
	if(PORT_ID >= NUM_OF_PORTS)
	{
		/*do nothing*/
	}
	else
	{
		switch(PORT_ID)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*
 * return the value for the given pin
 */
uint8 readPin(uint8 PORT_ID, uint8 PIN_ID)
{
	uint8 pin_value = LOGIC_LOW;

	if(PORT_ID >= NUM_OF_PORTS || PIN_ID >= NUM_OF_PINS_PER_PORT)
	{
		/*do nothing*/
	}
	else
	{
		/* Read the pin value as required */
		switch(PORT_ID)
		{
		case PORTA_ID:
			if(BIT_IS_SET(PINA,PIN_ID))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if(BIT_IS_SET(PINB,PIN_ID))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if(BIT_IS_SET(PINC,PIN_ID))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if(BIT_IS_SET(PIND,PIN_ID))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}

/*
 * Write the given value in the given pin
 */
void writePin(uint8 PORT_ID, uint8 PIN_ID, uint8 value )
{
	if(PORT_ID >= NUM_OF_PORTS || PIN_ID >= NUM_OF_PINS_PER_PORT)
	{
		/*do nothing*/
	}
	else
	{
		/* Read the pin value as required */
		switch(PORT_ID)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
				SET_BIT(PORTA, PIN_ID);
			else
				CLEAR_BIT(PORTA, PIN_ID);

			break;
		case PORTB_ID:
			if(value == LOGIC_HIGH)
				SET_BIT(PORTB, PIN_ID);
			else
				CLEAR_BIT(PORTB, PIN_ID);

			break;
		case PORTC_ID:
			if(value == LOGIC_HIGH)
				SET_BIT(PORTC, PIN_ID);
			else
				CLEAR_BIT(PORTC, PIN_ID);

			break;
		case PORTD_ID:
			if(value == LOGIC_HIGH)
				SET_BIT(PORTD, PIN_ID);
			else
				CLEAR_BIT(PORTD, PIN_ID);

			break;
		}
	}
}

/*
 * read pin register for the given port
 */
uint32 readPort(uint8 PORT_ID)
{
	uint32 port_value = LOGIC_LOW;
	if(PORT_ID >= NUM_OF_PORTS)
	{
		/*do nothing*/
	}
	else
	{
		/* Read the pin value as required */
		switch(PORT_ID)
		{
		case PORTA_ID:
			port_value = PINA;
			break;
		case PORTB_ID:
			port_value = PINB;
			break;
		case PORTC_ID:
			port_value = PINC;
			break;
		case PORTD_ID:
			port_value = PIND;
			break;
		}
	}
	return port_value;
}
/*
 * write the given value on the given port
 */
void writePort(uint8 PORT_ID, uint32 value)
{
	if(PORT_ID >= NUM_OF_PORTS)
	{
		/*do nothing*/
	}
	else
	{
		/* Read the pin value as required */
		switch(PORT_ID)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

