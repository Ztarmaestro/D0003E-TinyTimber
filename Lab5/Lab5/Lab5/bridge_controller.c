/*
 * Lab5.c
 *
 * Created: 2017-04-01 18:16:00
 *
 */ 

#include <avr/io.h>
#include "bridge_controller.h"
#include "usart.h"



void carSensors(bridgeController *Self, uint8_t input){
	if (input == 0x1){
		Self->northBuffer = Self->northBuffer + 1;
	}
	if (input == 0x2){
		Self->northBuffer = Self->northBuffer - 1;
	}
	if (input == 0x4){
		Self->southBuffer = Self->southBuffer + 1;
	}
	if (input == 0x8){
		Self->southBuffer = Self->southBuffer - 1;
	}
}

void bridgeSensor(bridgeController *self, int arg){
	if (self->northBuffer != 0 && self->northIsGreen == 1){
		self->northBuffer = self->northBuffer - 1;
		self->carOnBridge = 1;
		AFTER(MSEC(1000), self, bridgeSensor, 0);
	}
	
	if (self->southBuffer != 0 && self->southIsGreen == 1){
		self->southBuffer = self->southBuffer - 1;
		self->carOnBridge = 1;
		AFTER(MSEC(1000), self, bridgeSensor, 0);
	}
	else{
		return;
	}
}




//Make sure 5 sec has gone since Slight turned red
//Turn Nlight green and call Nbridge_sensor()
void Ngreenlight(bridgeController *self, int arg){
	if (self->carOnBridge == 0 && self->northIsGreen == 0){
		self->northIsGreen = 1;
		self->southIsGreen = 0;
	}
}



//Turn Slight green and call Sbridge_sensor()
void Sgreenlight(bridgeController *self, int arg){
	if (self->carOnBridge == 0 && self->southIsGreen == 0){
		self->southIsGreen = 1;
		self->northIsGreen = 0;
	}	
}

//LEGACY CODE FOR CAR SENSOR
/*
//Car arrive, add to buffer
void Ncar_sensor(bridgeController *self, int arg){
	self->northBuffer = self->northBuffer + 1;
}
//Car arrive, add to buffer
void Scar_sensor(bridgeController *self, int arg){

	self->southBuffer = self->southBuffer + 1;
}*/

//LEGACY CODE FOR BRIDGE SENSOR
/*
//Check if buffer is not 0 and light is green
//Remove car from buffer, wait 1 sec, call self again.
//If buffer is 0 do nothing
void Nbridge_sensor(bridgeController *self, int arg){
	if (self->northBuffer != 0 && self->northIsGreen == 1){
		self->northBuffer = self->northBuffer - 1;
		self->carOnBridge = 1;
		AFTER(MSEC(1000), self, Nbridge_sensor, int arg);
	}
	else{
		return;
	}
}
//Check if buffer is not 0 and light is green
//Remove car from buffer, wait 1 sec, call self again.
//If buffer is 0 do nothing
void Sbridge_sensor(bridgeController *self, int arg){

	if (self->southBuffer != 0 && self->southIsGreen == 1){
		self->southBuffer = self->southBuffer - 1;
		self->carOnBridge = 1;
		AFTER(MSEC(1000), self, Sbridge_sensor, int arg);
	}
	else{
		return;
	}
}
*/
