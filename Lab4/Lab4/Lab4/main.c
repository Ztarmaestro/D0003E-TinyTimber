/*
 * Lab4.c
 *
 * Created: 2017-02-28 09:59:27
 * Author : jespe
 */ 

#include <avr/io.h>
#include "GUI.h"
#include "pulse.h"
#include "joystick.h"
#include "TinyTimber.h"
#include "init.h"
#include <avr/interrupt.h>

GUI gui = initGUI(0,0);
Pulse pulse1 = initPulse(0,0,0,0,0,&gui);
Pulse pulse2 = initPulse(0,4,0,0,0,&gui);

Joystick joy = initJoystick(&pulse1, &pulse2, &pulse1);


void start(Joystick *self, int arg){
	ASYNC(self ,updateLCD, 0);
}

int main(void)
{
	sei();
	LCD_Init();
	LCDDR13 = 0xF;
	INSTALL(&joy, pinEdoSOMETHING ,IRQ_PCINT0);
	INSTALL(&joy, pinBdoSOMETHING ,IRQ_PCINT1);
	return TINYTIMBER(&joy,start,0);
   
   /* TINYTIMBER( T *obj, int (*meth)(T*,A), A arg ); */

}

