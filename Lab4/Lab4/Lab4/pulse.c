#include "pulse.h"
#include "TinyTimber.h"
#include <avr/io.h>

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
void switchLeftPulse(Pulse *self, int arg){
	if(self->position == 4){
		self->position = 0;
	}

}
void switchRightPulse(Pulse *self, int arg){
	if(self->position == 0){
		self->position = 4;
	}
}