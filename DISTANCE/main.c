/*
 * main.c
 *
 *  Created on: 17 Oct 2022
 *      Author: Amr Issa
 */
#include "gpio.h"
#include "icu.h"
#include "lcd.h"
#include "std_types.h"
#include"ultrasonic.h"
#include<avr\io.h>
#include <avr/interrupt.h>




int main()
{
	SREG |= (1<<7);
	uint16 distance=0;
	Ultrasonic_init();
	LCD_init();
	LCD_displayString("Distance=     cm");

	while(1)
	{
	distance=Ultrasonic_readDistance();
	LCD_moveCursor(0,11);
	LCD_intgerToString(distance);
	if(distance<10)
	{

		LCD_displayString("  ");
	}
	if(distance>10&&distance<100)
	{
		LCD_displayString(" ");
	}

	}
}

