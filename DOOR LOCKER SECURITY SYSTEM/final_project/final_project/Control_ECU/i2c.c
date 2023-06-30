/*
 * i2c.c
 *
 *  Created on: Nov 3, 2022
 *      Author: OMR
 /
 *
 */
#include"i2c.h"
#include<avr/io.h>
#include"common_macros.h"
void TWI_init(const TWI_ConfigType * Config_Ptr)
{
	/*calculate TWBR depending on SCL freq*/
	uint8 bit_rate = (uint8)(((cpu_clk_freq / Config_Ptr->bit_rate)-16)/2);
	TWBR = bit_rate;
	TWSR = pre_1 ;

	/*set TWEN to enable TWI*/
	TWCR |= (1<<TWEN);

	/*set an address for the device when its a slave*/
	TWAR = (Config_Ptr -> address)<<1;
}

void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));}

void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
	/*put data to be sent*/
	TWDR = data;

	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/*
		 * Clear the TWINT flag before sending the stop bit TWINT=1
		 * Enable TWI Module TWEN=1
		 * set TWEA to enable ACK
		 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWEA);

	 /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
	/*read data*/
	return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
			 * Clear the TWINT flag before sending the stop bit TWINT=1
			 * Enable TWI Module TWEN=1
			 */
		TWCR = (1 << TWINT) | (1 << TWEN);

		 /* Wait for TWINT flag set in TWCR Register (data received successfully) */
	    while(BIT_IS_CLEAR(TWCR,TWINT));
		/*read data*/
		return TWDR;
}

uint8 TWI_getStatus(void)
{
	/*clear prescaler bits to get correct status*/
	return(TWSR & 0xF8);
}
