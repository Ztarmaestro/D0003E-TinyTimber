

#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include "TinyTimber.h"
#include "pulse.h"
typedef struct {
	Object super;
	Pulse *Pulse1;
	Pulse *Pulse2;
	Pulse *current;
} Joystick;

#define initJoystick(Pulse1, Pulse2, current){initObject(), Pulse1, Pulse2, current}
void pinBdoSOMETHING(Joystick *self, int arg);
void pinEdoSOMETHING(Joystick *self, int arg);
void scroll(Joystick *self, int arg);
void updateLCD(Joystick *self, int arg);
void freqDisplay(Joystick *self, int arg);

#endif /* JOYSTICK_H_ */