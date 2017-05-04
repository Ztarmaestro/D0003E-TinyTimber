/*
 * usart.h
 *
 * Created: 2017-04-14 15:23:25
 *  Author: jesgla-2
 */ 


#ifndef USART_H_
#define USART_H_
#include "bridge_controller.h"

typedef struct{
	Object super;
	bridgeController *bController;
	uint8_t Input;
}usart;


void usartcable(usart *self, int arg);
#endif /* USART_H_ */