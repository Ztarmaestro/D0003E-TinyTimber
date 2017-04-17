/*
 * usart.h
 *
 * Created: 2017-04-14 15:23:25
 *  Author: jesgla-2
 */ 


#ifndef USART_H_
#define USART_H_

typedef struct{
	Object super;
	bridgeController *bController;
	char Input;
}usart;



#endif /* USART_H_ */