#include "pulse.h"
#include "TinyTimber.h"
#include <avr/io.h>
#include "joystick.h"
void increaseFreq(Pulse *self, int arg){
	if (self->freq <= 98){
		self->freq = self->freq+1;
	}
}

void decreaseFreq(Pulse *self, int arg){
	if (self->freq >=1){
		self->freq = self->freq-1;
	}
}

void memoryFreq(Pulse *self, int arg){
	
	if ((self->freq != 0) && (self->memFlag == 0)){
		self->memory = self->freq;
		self->freq = 0;
		self->memFlag = 1;
	}else{
		self->freq = self->memory;
		self->memFlag = 0;
		
	}
}
void switchLeftPulse(Joystick *self, int arg){
	if(self->current->position == 4){
		self->current = self->Pulse1;
	}

}
void switchRightPulse(Joystick *self, int arg){
	if(self->current->position == 0){
		self->current = self->Pulse2;
	}
}