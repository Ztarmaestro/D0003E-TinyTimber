/*
 * bridge_controller.h
 *
 * Created: 2017-04-02 16:21:17
 *  Author: jesgla-2
 */ 


#ifndef BRIDGE_CONTROLLER_H_
#define BRIDGE_CONTROLLER_H_
#include "TinyTimber.h"

typedef struct  {
	Object super;
	int northIsGreen;
	int southIsGreen;
	int northBuffer;
	int southBuffer; 
	int carOnBridge;
	
} bridgeController;

void Ncar_sensor(bridgeController *self, int arg);
void Nbridge_sensor(bridgeController *self, int arg);
void Scar_sensor(bridgeController *self, int arg);
void Sbridge_sensor(bridgeController *self, int arg);
void Ngreenlight(bridgeController *self, int arg);
void Sgreenlight(bridgeController *self, int arg);

#endif /* BRIDGE_CONTROLLER_H_ */