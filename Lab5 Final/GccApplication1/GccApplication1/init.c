#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyTimber.h"

void LCD_Init(void)
{

/*setting for the AVR*/
CLKPR = 0x80;
CLKPR = 0x00;

/*LCD ENABLE; LOW POWER WAVEFORM*/
LCDCRA = (1<<LCDEN) | (1<<LCDAB);
/*ASYNC CLOCK; 1/4 duty; 1/3 bias; 25 segments */
LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2)| (1<<LCDPM1)| (1<<LCDPM0);
/*Clock N=16 D = 8*/
LCDFRR = (1<<LCDCD2) |(1<<LCDCD1) |(1<<LCDCD0);
/*Drivetime 300 3.35 volt */
LCDCCR = (1<<LCDCC3) |(1<<LCDCC2) |(1<<LCDCC1) |(1<<LCDCC0);

	
//usart init	
UBRR0H = (51>>8);
UBRR0L = 51;

/* Enable Reciever & Transmitter; Enable interrupt on clear transmit buffer*/
UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
/* Set Character size 8, One stop bit*/
UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);

}