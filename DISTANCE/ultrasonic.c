/*
 * ultrasonic.c
 *
 *  Created on: 17 Oct 2022
 *      Author: Amr Issa
 */
#include"ultrasonic.h"
#include "gpio.h"
#include "util/delay.h"
#include "icu.h"


Icu_ConfigType configurations;
uint8 finish_flag=0;
uint8 g_edgeCount = 0;
uint16 Time_HIGH=0;
uint16 Distance_cm;


void Ultrasonic_init(void)
{
	configurations.clock=F_CPU_8;
	configurations.edge=RISING;
	Icu_init(&configurations);
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(TRIGGER_PORT_ID,TRIGGER_PIN_ID,PIN_OUTPUT);



}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(20);
	GPIO_writePin(TRIGGER_PORT_ID,TRIGGER_PIN_ID,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{

	Ultrasonic_Trigger();
	while(finish_flag==0);
	Distance_cm=(uint16)(Time_HIGH/58)+1; //+1 to avoid using floats and since the reading is off the lcd displays one number less

	finish_flag=0;
	return Distance_cm;
}
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if (g_edgeCount==1)
	{
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(FALLING);
	}
	if(g_edgeCount==2)
	{
		Time_HIGH=Icu_getInputCaptureValue();
		finish_flag=1;
		Icu_clearTimerValue();
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount=0;

	}

}

