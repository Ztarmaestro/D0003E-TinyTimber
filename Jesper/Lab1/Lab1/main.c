/*
 * Lab1.c
 *
 * Created: 2017-01-17 12:55:36
 * Author : jesper
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>

//register variables
char reg1;
char reg2;
char reg3;
char reg4;
//for the button
int isPressed = 0;
long prime = 2;


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
	//timer with prescaler 256
	TCCR1B = (1<<CS12);
	//button setting
	PORTB = (1 << PINB7);
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
		case 1:
			LCDDR0  = (LCDDR0 & 0xF0) | reg1;
			LCDDR5  = (LCDDR5 & 0xF0) | reg2;
			LCDDR10 = (LCDDR10 & 0xF0) | reg3;
			LCDDR15 = (LCDDR15 & 0xF0) | reg4;
			
			break;
		case 2:
			LCDDR0  = (LCDDR0 & 0x0F) | reg1 << 4;
			LCDDR5  = (LCDDR5 & 0x0F) | reg2 << 4;
			LCDDR10 = (LCDDR10 & 0x0F) | reg3 << 4;
			LCDDR15 = (LCDDR15 & 0x0F) | reg4 << 4;
			break;
		case 3:
			LCDDR1  = (LCDDR1 & 0xF0) | reg1;
			LCDDR6  = (LCDDR6 & 0xF0) |reg2;
			LCDDR11 = (LCDDR11 & 0xF0) |reg3;
			LCDDR16 = (LCDDR16 & 0xF0) |reg4;
			break;
			
		case 4:
			LCDDR1  = (LCDDR1 & 0x0F) | reg1 << 4;
			LCDDR6  = (LCDDR6 & 0x0F) | reg2 << 4;
			LCDDR11 = (LCDDR11 & 0x0F) | reg3 << 4;
			LCDDR16 = (LCDDR16 & 0x0F) | reg4 << 4;
			break;

		case 5:
			LCDDR2  = (LCDDR2 & 0xF0) |reg1;
			LCDDR7  = (LCDDR7 & 0xF0) |reg2;
			LCDDR12 = (LCDDR12 & 0xF0) |reg3;
			LCDDR17 = (LCDDR17 & 0xF0) |reg4;
			break;

		case 6:
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
//takes a long int and converts it to a str and writes the 6 least significant digits
void writeLong(long i)
{	
	char c;
									//k is the number of positions avaliable
	for (int k = 6; k > 0; k--) {
									//if the list is shorter than 6 this will prevent zeros to be printed at empty positions
		if (k != 0 && i==0) {
			break;
		}
									//mod 10 takes last digit /10 removes last digit
		c = i % 10;
		writeChar(c, k);
		i = i / 10;
	}
	

}


//helper function, checking if a number is prime
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
//prints primes on the AVR
void primes()
{
	
	long i = 25000;

		if (is_prime(prime) == 1){		
			writeLong(i);
		}
		i++;
	
}
//prime using pointers (just testing how pointers work, still not sure)
void primes2(unsigned long *l)
{

		while(1){
		if (is_prime(*l) == 1){
			//prime = *l;
			writeLong(*l);
			*l += 1;
			break;
			}

		*l += 1;
	}
}

//blink some segemnts on the lcd
void blink()
{
	unsigned int timer1 = 0x3D08;
	//xoring the register and then resets TCNT1
	if (TCNT1 >= timer1){
		LCDDR13 ^= 0x01;
		TCNT1 = 0;
	}
	
}
//turn on/off some segements on lcd
void button()
{
	//int isPressed = 0;
	while(1){
	//"resets" the button when it has been pressed
		if (((1 << PINB) == 0) && (isPressed == 1)){
			isPressed = 0;
		}
		//if the segment is on, turn it off, if segment is off turn it on
		if (((1 << PINB) == 1) && (isPressed == 0)){
			if ((LCDDR18 == 0x01) && (isPressed == 0)){
				LCDDR18 = 0x00;
			} 
			else{
				LCDDR18 = 0x01;	
			}
			isPressed = 1;
		}
	}
}

//removed the while loop from "blink" and made variable global
void button2()
{
		if (((1 << PINB) == 0) && (isPressed == 1)){
			isPressed = 0;
		}
		if (((1 << PINB) == 1) && (isPressed == 0)){
			if ((LCDDR18 == 0x01) && (isPressed == 0)){
				LCDDR18 = 0x00;
			}
			else{
				LCDDR18 = 0x01;
			}
			isPressed = 1;
		}
	}


int main(void)
{
	LCD_Init();
	//primes();
	writeChar('1',6);
	//primes();
	//part 1
	//writeLong(11186545);
	//part2
/*
	while(1){
		blink();
		}*/
	//part3
	//button();
	
	//part 4

/*
	unsigned long startPrime = 25000;
	while(1){
		blink();
		primes2(&startPrime);
		button2();
	}*/
	
	
	
	
}


