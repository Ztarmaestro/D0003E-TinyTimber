/*
 * pulse.h
 *
 * Created: 2017-03-01 13:54:39
 *  Author: jespe
 */ 
#include "TinyTimber.h"
#include "GUI.h"
#include <avr/io.h>

#ifndef PULSE_H_
#define PULSE_H_

typedef struct{
	Object super;
	int freq;
	int position;
	int memory;
	int memFlag;
	GUI *GUI;
}Pulse;

#define initPulse(freq, position, memory,memFlag, GUI){initObject(), freq, position, memory, memFlag, GUI}

void increaseFreq(Pulse *self, int arg);
void decreaseFreq(Pulse *self, int arg);
void memoryFreq(Pulse *self, int arg);
#endif /* PULSE_H_ */