#include "joystick.h"
#include "TinyTimber.h"
#include "pulse.h"
#include <avr/io.h>

void pinBdoSOMETHING(Joystick *self, int arg){

	if (!(PINB &(1<<PINB6))){
		increaseFreq(self->current, 0);
	}
	if (!(PINB &(1<<PINB7))){
		decreaseFreq(self->current, 0);
	}
	if (!(PINB &(1<<PINB4))){
		memoryFreq(self->current, 0);
	}
	

}

void pinEdoSOMETHING(Joystick *self, int arg){

	if (!(PINE &(1<<PINE2))){
		switchLeftPulse(self->current, 0);
	}
	if (!(PINE &(1<<PINE3))){
		switchRightPulse(self->current, 0);
	}
	
}