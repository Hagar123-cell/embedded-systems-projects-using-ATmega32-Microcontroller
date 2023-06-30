/*
 * buzzer.c
 *
 *  Created on: Nov 5, 2022
 *      Author: OMR
 */
#include"buzzer.h"
#include"GPIO.h"
#include"std_types.h"
void Buzzer_init(void)
{
    setPinDirection( PORTB_ID, PIN3_ID, PIN_OUTPUT);
    writePin(PORTB_ID, PIN3_ID, LOGIC_LOW);
}

void Buzzer_on(void)
{
    writePin(PORTB_ID, PIN3_ID, LOGIC_HIGH);

}

void Buzzer_off(void)
{
    writePin(PORTB_ID, PIN3_ID, LOGIC_LOW);
}

