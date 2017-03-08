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
		ASYNC(self->current, memoryFreq, 0);
	}
	ASYNC(self,updateLCD,0);
	
}


void freqDisplay(Joystick *self, int arg){
	
	//xor output av freq from pin
	if(PORTE & (1<<PINE4)){
		PORTE ^= (1<<PINE4);
	}
/*
	if(PORTE & (1<<PINE6)){
		PORTE ^= (1<<PINE6);
	}*/
	AFTER(MSEC(500/self->current->freq), self, freqDisplay, 0);
}


void pinEdoSOMETHING(Joystick *self, int arg){
	if (!(PINE &(1<<PINE2))){
		LCDDR13 = 0xF;
		self->current = self->Pulse1;
			if (self->Pulse1->freqDisplayFlag == 0){
				self->Pulse1->freqDisplayFlag = 1;
				ASYNC(self->Pulse1, freqDisplay, 0);
			}
		//switchToRight
	}
	if (!(PINE &(1<<PINE3))){
		LCDDR13 = 0;
		self->current = self->Pulse2;
			if (self->Pulse2->freqDisplayFlag == 0){
				self->Pulse2->freqDisplayFlag = 1;
				ASYNC(self->Pulse2, freqDisplay, 0);
			}
		//switchToLeft
	}
	
}