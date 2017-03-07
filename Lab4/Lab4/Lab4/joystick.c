#include "joystick.h"
#include "TinyTimber.h"
#include "pulse.h"
#include <avr/io.h>
#include "GUI.h"
#include "main.h"


void scroll(Joystick *self, int arg){
	if(!(PINB &(1<<PINB6))){
		ASYNC(self->current, increaseFreq, 0);
		AFTER(MSEC(arg), self, scroll, arg+200);

	}
		if(!(PINB &(1<<PINB7))){
			ASYNC(self->current, decreaseFreq, 0);
			AFTER(MSEC(arg), self, scroll, arg+200);

		}
	ASYNC(self, start, 0);
}

 void updateLCD(Joystick *self, int arg){
	 printAt(self->Pulse1->freq, self->Pulse1->position);
	 printAt(self->Pulse2->freq, self->Pulse2->position);
 }
void pinBdoSOMETHING(Joystick *self, int arg){

	if (!(PINB &(1<<PINB6))){
		ASYNC(self, scroll, 500);
	}
	if (!(PINB &(1<<PINB7))){
		ASYNC(self, scroll, 500);
	}
	if (!(PINB &(1<<PINB4))){
		memoryFreq(self->current, 0);
	}
	
}



void pinEdoSOMETHING(Joystick *self, int arg){
	if (!(PINE &(1<<PINE2))){
			LCDDR13 ^= 0xF;
		self->current = self->Pulse1;
		//switchToRight(self->current, 0);
	}
	if (!(PINE &(1<<PINE3))){
		self->current = self->Pulse2;
		//switchToLeft(self->current, 0);
	}
	
}