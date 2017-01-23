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

//register variables
int reg1;
int reg2;
int reg3;
int reg4;
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
	
}
//cases for number 0-9
void caseNumbers(char ch)
{
	//cases for every number 0-9
	switch (ch)
	{
		case 0 :
			reg1 = 0x01;
			reg2 = 0x05;
			reg3 = 0x05;
			reg4 = 0x01;
			break;
		case 1 :
			reg1 = 0x00;
			reg2 = 0x01;
			reg3 = 0x01;
			reg4 = 0x00;
			break;
		case 2 :
			reg1 = 0x01;
			reg2 = 0x01;
			reg3 = 0x0E;
			reg4 = 0x01;
			break;
		case 3 :
			reg1 = 0x01;
			reg2 = 0x01;
			reg3 = 0x0B;
			reg4 = 0x01;
			break;
		case 4 :
			reg1 = 0x00;
			reg2 = 0x05;
			reg3 = 0x0B;
			reg4 = 0x00;
			break;
		case 5 :
			reg1 = 0x01;
			reg2 = 0x04;
			reg3 = 0x0B;
			reg4 = 0x01;
			break;
		case 6 :
			reg1 = 0x01;
			reg2 = 0x04;
			reg3 = 0x0F;
			reg4 = 0x01;
			break;
		case 7 :
			reg1 = 0x01;
			reg2 = 0x01;
			reg3 = 0x01;
			reg4 = 0x00;
			break;
		case 8 :
			reg1 = 0x01;
			reg2 = 0x05;
			reg3 = 0x0F;
			reg4 = 0x01;
			break;
		case 9 :
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
			LCDDR0  = (LCDDR0 & 0xF0) | reg1  ;
			LCDDR5  = (LCDDR5 & 0xF0) | reg2 ;
			LCDDR10 = (LCDDR10 & 0xF0) | reg3 ;
			LCDDR15 = (LCDDR15 & 0xF0) | reg4 ;
			
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



long is_prime(long i)
{
	long rest;
	for (long n = 2; n < i; n++){
		rest = i % n;
		if (rest == 0){
			return 0;		
		}
	}
	return 1;
}

void primes()
{
	long i = 1;
	while (i > 0){
		if (is_prime(i) == 1){		
			writeLong(i);
		}
		i++;
	}
}

int main(void)
{
	
	LCD_Init();
	primes();
	
}

