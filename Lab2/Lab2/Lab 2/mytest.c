#include "tinythreads.h"
#include <avr/io.h>
#include <avr/iom169p.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <avr/interrupt.h>
//register variables
char reg1;
char reg2;
char reg3;
char reg4;
int pp;
mutex mute = MUTEX_INIT;
//settings for avr
void LCD_Init(void)
{
	//setting for the AVR//
	CLKPR = 0x80;
	CLKPR = 0x00;
	//external async clock, 1/3 bias, 1/4 duty cycle, 25 segments
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX0) | (1 << LCDMUX1) | (1 << LCDPM0) | (1 << LCDPM1) | (1 << LCDPM2);
	//clock divider N=8
	LCDFRR = (1 << LCDCD0) | (1 << LCDCD1) | (1 << LCDCD2);
	//LCD low power, no frame interrupt no blanking
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	//Drive time 300ms, control voltage 3,35V
	LCDCCR = (1 << LCDCC0) | (1 << LCDCC1) | (1 << LCDCC2) | (1 << LCDCC3);
/*
	//timer with prescaler 256
	TCCR1B = (1<<CS12);
	//button setting
	PORTB = (1 << PINB7);*/

}
//cases for number 0-9
void caseNumbers(char ch)
{
	//cases for every number 0-9
	switch (ch)
	{
		case '0' :
		reg1 = 0x01;
		reg2 = 0x05;
		reg3 = 0x05;
		reg4 = 0x01;
		break;
		case '1' :
		reg1 = 0x00;
		reg2 = 0x01;
		reg3 = 0x01;
		reg4 = 0x00;
		break;
		case '2' :
		reg1 = 0x01;
		reg2 = 0x01;
		reg3 = 0x0E;
		reg4 = 0x01;
		break;
		case '3' :
		reg1 = 0x01;
		reg2 = 0x01;
		reg3 = 0x0B;
		reg4 = 0x01;
		break;
		case '4' :
		reg1 = 0x00;
		reg2 = 0x05;
		reg3 = 0x0B;
		reg4 = 0x00;
		break;
		case '5':
		reg1 = 0x01;
		reg2 = 0x04;
		reg3 = 0x0B;
		reg4 = 0x01;
		break;
		case '6' :
		reg1 = 0x01;
		reg2 = 0x04;
		reg3 = 0x0F;
		reg4 = 0x01;
		break;
		case '7' :
		reg1 = 0x01;
		reg2 = 0x01;
		reg3 = 0x01;
		reg4 = 0x00;
		break;
		case '8' :
		reg1 = 0x01;
		reg2 = 0x05;
		reg3 = 0x0F;
		reg4 = 0x01;
		break;
		case '9' :
		reg1 = 0x01;
		reg2 = 0x05;
		reg3 = 0x0B;
		reg4 = 0x01;
		break;
	}

}
//cases for all positions on the avr
void casePosition(int pos)
{
	//cases for each position
	//Bitmask and shifts are used to manipulate bits
	switch (pos)
	{
		case 0:
		LCDDR0  = (LCDDR0 & 0xF0) | reg1;
		LCDDR5  = (LCDDR5 & 0xF0) | reg2;
		LCDDR10 = (LCDDR10 & 0xF0) | reg3;
		LCDDR15 = (LCDDR15 & 0xF0) | reg4;
		
		break;
		case 1:
		LCDDR0  = (LCDDR0 & 0x0F) | reg1 << 4;
		LCDDR5  = (LCDDR5 & 0x0F) | reg2 << 4;
		LCDDR10 = (LCDDR10 & 0x0F) | reg3 << 4;
		LCDDR15 = (LCDDR15 & 0x0F) | reg4 << 4;
		break;
		case 2:
		LCDDR1  = (LCDDR1 & 0xF0) | reg1;
		LCDDR6  = (LCDDR6 & 0xF0) |reg2;
		LCDDR11 = (LCDDR11 & 0xF0) |reg3;
		LCDDR16 = (LCDDR16 & 0xF0) |reg4;
		break;
		
		case 3:
		LCDDR1  = (LCDDR1 & 0x0F) | reg1 << 4;
		LCDDR6  = (LCDDR6 & 0x0F) | reg2 << 4;
		LCDDR11 = (LCDDR11 & 0x0F) | reg3 << 4;
		LCDDR16 = (LCDDR16 & 0x0F) | reg4 << 4;
		break;

		case 4:
		LCDDR2  = (LCDDR2 & 0xF0) |reg1;
		LCDDR7  = (LCDDR7 & 0xF0) |reg2;
		LCDDR12 = (LCDDR12 & 0xF0) |reg3;
		LCDDR17 = (LCDDR17 & 0xF0) |reg4;
		break;

		case 5:
		LCDDR2  = (LCDDR2 & 0x0F) | reg1 << 4;
		LCDDR7  = (LCDDR7 & 0x0F) | reg2 << 4;
		LCDDR12 = (LCDDR12 & 0x0F) | reg3 << 4;
		LCDDR17 = (LCDDR17 & 0x0F) | reg4 << 4;
		break;

		
		

	}
}

//function to write a char at a position
void writeChar(char ch, int pos)
{
	
	caseNumbers(ch);
	casePosition(pos);
	
}
long is_prime(long i)
{
	long rest;
	for (long n = 2; n < i; n++){			//sqrt n is faster
		rest = i % n;
		if (rest == 0){
			return 0;
		}
	}
	return 1;
}

void printAt(long num, int pos) {
	lock(&mute);
	pp = pos;
	writeChar( (num % 100) / 10 + '0', pp);
	int loop_test;
	for(int test; test < 1000; test++){
		
		loop_test++;
		}
	pp++;
	writeChar( num % 10 + '0', pp);
	unlock(&mute);
//	yield();
}

void computePrimes(int pos) {
	long n;

	for(n = 1; ; n++) {
		if (is_prime(n)) {
			printAt(n, pos);
		}
	}
}

ISR(PCINT1_vect){
		if ((1 << PINB) == 0){
			yield();
		}
}
ISR(TIMER1_COMPA_vect){
	yield();
}

int main() {
	LCD_Init();
	spawn(computePrimes, 0);
	computePrimes(3);
}
