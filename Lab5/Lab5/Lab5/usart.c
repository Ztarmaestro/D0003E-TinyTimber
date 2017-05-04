/*
 * usart.c
 *
 * Created: 2017-04-14 15:23:11
 *  Author: jesgla-2
 */ 

#include "usart.h"

void usartcable (usart *self){
	self->Input = UDR0;
	uint8_t input = self->Input;
	ASYNC(&bridgeController, carSensors, input);
}

