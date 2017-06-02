/*
 * GccApplication1.c
 *
 * Created: 2017-05-05 10:34:01
 * Author : jesgla-2
 */ 

#include <avr/io.h>
#include "TinyTimber.h"
#include "init.h"
#include <avr/interrupt.h>

typedef struct  {
	Object super;
	int northIsGreen;
	int southIsGreen;
	int northBuffer;
	int southBuffer;
	int carOnBridge;
	int timeoutCounter;
	
}bridgeController;

typedef struct{
	Object super;
	bridgeController * bController;
	uint8_t Input;
}usart;

#define initbridgeController(northIsGreen, southIsGreen, northBuffer, southBuffer, carOnBridge, timeoutCounter){initObject(), northIsGreen, southIsGreen, northBuffer, southBuffer, carOnBridge, timeoutCounter}
#define initUsart(bController, Input){initObject(), bController, Input}

bridgeController BC = initbridgeController(0,0,0,0,0,0);
usart yusart = initUsart(&BC,0);

void usart_send(usart *Self, uint8_t Data){
	LCDDR8=1;
	/*while (!(UCSR0A & (1<<RXC0)));*/
	UDR0 = Data;
}

void carSensors(bridgeController *self, uint8_t input){
	if (input == 0x1){
		self->northBuffer = self->northBuffer + 1;
	}
	if (input == 0x2){
		self->northBuffer = self->northBuffer - 1;
	}
	if (input == 0x4){
		self->southBuffer = self->southBuffer + 1;
	}
	if (input == 0x8){
		self->southBuffer = self->southBuffer - 1;
	}
}

void bridgeSensor(bridgeController *Self, int arg)
{
	
	if((Self->southBuffer == 0) && (Self->northBuffer == 0)){
		//Both Red
		ASYNC(&yusart,usart_send,0xA); 
		AFTER(MSEC(1000),Self,bridgeSensor,0);

	}

	else if ((Self->southBuffer > 0)||(Self->northBuffer > 0)){
		if(arg == 0){
			if((Self->timeoutCounter <= 5) && (Self->southBuffer > 0)){
				ASYNC(&yusart,usart_send,0x6); // South Green
				if((Self->northBuffer)>0){
					Self->timeoutCounter +=1;	
				}
				AFTER(MSEC(1000),Self,bridgeSensor,0);
			}
			//south == 0 call urself with and set arg to 1
			
			else{
				Self->timeoutCounter = 0;
				arg = 1;
				ASYNC(&yusart,usart_send,0xA); 
				AFTER(MSEC(5000),Self,bridgeSensor,arg);	
			}
		}	
		else if(arg==1){
			if((Self->timeoutCounter <=5) && (Self->northBuffer > 0)){ 
				ASYNC(&yusart,usart_send,0x9); //North Green
				if((Self->southBuffer)>0){
					Self->timeoutCounter +=1;
				}
				
				AFTER(MSEC(1000),Self,bridgeSensor,1);
			}
			else{
				Self->timeoutCounter = 0;
				arg = 0;
				ASYNC(&yusart,usart_send,0xA); 
				AFTER(MSEC(5000),Self,bridgeSensor,arg);
			}
		}
	}
}

void usartcable (usart *self, int arg){
	/*while (!(UCSR0A & (1<<RXC0)));*/
	self->Input = UDR0;
	uint8_t input = self->Input;
	ASYNC(&BC, carSensors, input);
}

void start(usart *self, int arg){
	UDR0 = 0xA;
	ASYNC(&BC, bridgeSensor, 0);
}

int main(void)
{
    LCD_Init();
   	INSTALL(&yusart, usartcable, IRQ_USART0_RX);
   	sei();
   	return TINYTIMBER(&yusart, start, NULL);
}

