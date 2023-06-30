/*
 * Mini_Project2.c
 *
 *  Created on: Sep 17, 2022
 *      Author: OMR
 */
#include <avr/io.h>
#include<AVR/interrupt.h>
#include <util/delay.h>
unsigned char hours = 0, minutes = 0, seconds = 0;
ISR(TIMER1_COMPA_vect)
{
	if(seconds == 59)
	{
		seconds = 0;
		if(minutes == 59)
		{
			minutes = 0;
			hours++;
		}
		else if(minutes != 59)
			minutes++;
	}
	else
		seconds++;

}
void timer1_CTC_init(void)
{
	SREG |= 1<<7;//enable i_bit
	TCCR1A = (1<<FOC1A);//configure non PWM mode & OCR1A as a compare register
	TCCR1B = (1<<ICNC1) | (1<<WGM12) | (1<<CS10) | (1<<CS11);
	/*
	 *disable ICU & OCR1A as a compare register & prescaler-> 64
	 */
	TIMSK = 1<<OCIE1A; //Output Compare A Match Interrupt EnablE
	TCNT1 = 0; //set initial value
	OCR1A = 15625;//set compare value
}

// RESET
ISR(INT0_vect)
{
	seconds = 0, minutes = 0, hours = 0;
}
void INT0_init(void)
{
	DDRD &= ~(1<<PD2);//CONFIGURE INT0 AS INPUT
	PORTD |= 1<<PD2;//INTERNAL PULL UP
	MCUCR |= (1<<ISC01);//with falling edge
	GICR |= (1<<INT0);//enable INT0
}

//PAUSE
ISR(INT1_vect)
{
	TCCR1B &= 0xF8;//NO CLK SOURSE
}
void INT1_init(void)
{
	DDRD &= ~(1<<PD3);//CONFIGURE INT1 AS INPUT
	MCUCR |= (1<<ISC10) | (1<<ISC11);//with RISING edge
	GICR |= (1<<INT1);//enable INT1
}


//resume
ISR(INT2_vect)
{
	TCCR1B |= (1<<CS00) | (1<<CS01);//
}
void INT2_init(void)
{
	DDRB &= ~(1<<PB2);//CONFIGURE INT2 AS INPUT
	PORTB |= 1<<PB2;//INTERNAL PULL UP
	MCUCSR = 0;//WITH FALLING EDGE
	GICR |= (1<<INT2);//enable INT1
}
int main()
{
	DDRC |= 0x0F;//FOR DECODER
	PORTC &= ~(0x0F);

	DDRA |= 0x3F;//enable/disable pins for the six 7-segments
	PORTA &= ~(0x3F);

	timer1_CTC_init();
	INT0_init();
	INT1_init();
	INT2_init();

	while(1)
	{
		PORTA = (PORTA & 0xC0) | (1<<0); //enable sec1
		PORTC = (PORTC & 0xF0) |(seconds % 10) ;
		_delay_ms(.5);
		PORTA = (PORTA & 0xC0) | (1<<1); //enable sec2
		PORTC = (PORTC & 0xF0) | (seconds / 10);
		_delay_ms(0.5);
		PORTA = (PORTA & 0xC0) | (1<<2); //enable min1
		PORTC = (PORTC & 0xF0) | (minutes % 10);
		_delay_ms(0.5);
		PORTA = (PORTA & 0xC0) | (1<<3); //enable min2
		PORTC = (PORTC & 0xF0) | (minutes / 10);
		_delay_ms(0.5);
		PORTA = (PORTA & 0xC0) | (1<<4); //enable hours1
		PORTC = (PORTC & 0xF0) | (hours / 10);
		_delay_ms(0.5);
		PORTA = (PORTA & 0xC0) | (1<<5); //enable hours2
		PORTC = (PORTC & 0xF0) | (hours / 10);
		_delay_ms(0.5);
	}

}
