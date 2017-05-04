#include <avr/io.h>
#include <avr/iom169p.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <avr/interrupt.h>
#include "GUI.h"


 //function to write a char at a position
 void writeChar(char ch, int pos)
 {
	 char reg1;
	 char reg2;
	 char reg3;
	 char reg4;

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

 void printAt(long num, int pos) 
 {
	
	 int pp = pos;
	 writeChar( (num % 100) / 10 + '0', pp);
	 pp++;
	 writeChar( num % 10 + '0', pp);

 }


