/*
 * writeApplication.c
 *
 * Created: 2017-01-18
 * Author : Erik Karlsson
 */

#include <avr/io.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void LCD_Init(void){
	/*
    TO-DO List:
		[x]drive time 300 microseconds,
		[x]contrast control voltage 3.35 V,
		[x]external asynchronous clock source,
		[x]1/3 bias,
		[x]1/4 duty cycle,
		[x]25 segments enabled,
		[x]prescaler setting N=16,
		[x]clock divider setting D=8,
		[x]LCD enabled,
		[x]low power waveform,
		[x]no frame interrupt,
		[x]no blanking
	*/

	/* Make the on-board processor run at its maximum speed */
	CLKPR = 0x80;
	CLKPR = 0x00;

	/* External asynchronous clock source, 1/3 Bias and 1/4 duty cycle, Segments 25 */
	LCDCRB = (1<<LCDCS) | (0<<LCD2B) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);

	/* Using 16 as prescaler selection, 8 as LCD Clock Divide */
	LCDFRR = (0<<LCDPS2) | (0<<LCDPS1) | (0<<LCDPS0) | (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);

	/* Set segment drive time to 300 ?s, set output voltage to 3.35V */
	LCDCCR = (0<<LCDDC2) | (0<<LCDDC1) | (0<<LCDDC0) | (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1) | (1<<LCDCC0);

	/* Enable LCD, default waveform, no interrupt enabled and no blanking */
	LCDCRA = (1<<LCDEN) | (0<<LCDAB) | (0<<LCDIE) | (0<<LCDBL);

}

void printChar(int pos, int row1, int row2, int row3, int row4){
	//cases for each position
	//Bitmask and shifts are used to manipulate bits
	switch (pos)
	{
		case 1:
		LCDDR0  = (LCDDR0 & 0xF0) | row1  ;
		LCDDR5  = (LCDDR5 & 0xF0) | row2 ;
		LCDDR10 = (LCDDR10 & 0xF0) | row3 ;
		LCDDR15 = (LCDDR15 & 0xF0) | row4 ;
		break;
		
		case 2:
		LCDDR0  = (LCDDR0 & 0x0F) | row1 << 4;
		LCDDR5  = (LCDDR5 & 0x0F) | row2 << 4;
		LCDDR10 = (LCDDR10 & 0x0F) | row3 << 4;
		LCDDR15 = (LCDDR15 & 0x0F) | row4 << 4;
		break;
		
		case 3:
		LCDDR1  = (LCDDR1 & 0xF0) | row1;
		LCDDR6  = (LCDDR6 & 0xF0) | row2;
		LCDDR11 = (LCDDR11 & 0xF0) |row3;
		LCDDR16 = (LCDDR16 & 0xF0) |row4;
		break;
		
		case 4:
		LCDDR1  = (LCDDR1 & 0x0F) | row1 << 4;
		LCDDR6  = (LCDDR6 & 0x0F) | row2 << 4;
		LCDDR11 = (LCDDR11 & 0x0F) | row3 << 4;
		LCDDR16 = (LCDDR16 & 0x0F) | row4 << 4;
		break;

		case 5:
		LCDDR2  = (LCDDR2 & 0xF0) |row1;
		LCDDR7  = (LCDDR7 & 0xF0) |row2;
		LCDDR12 = (LCDDR12 & 0xF0) |row3;
		LCDDR17 = (LCDDR17 & 0xF0) |row4;
		break;

		case 6:
		LCDDR2  = (LCDDR2 & 0x0F) | row1 << 4;
		LCDDR7  = (LCDDR7 & 0x0F) | row2 << 4;
		LCDDR12 = (LCDDR12 & 0x0F) | row3 << 4;
		LCDDR17 = (LCDDR17 & 0x0F) | row4 << 4;
		break;
	}
}

void writeChar(char ch, int pos){
	
	int row1;
	int row2;
	int row3;
	int row4;

	if (pos > 6){
		
	} else {
		
		int charToInt = (int)ch;

		if (charToInt >= 10){
			row1 = 0x8;
			row2 = 0x2;
			row3 = 0x0;
			row4 = 0xC;
			
			printChar(pos, row1, row2, row3, row4);	

		} else {
			
			if (charToInt == 0){
				row1 = 0x1;
				row2 = 0x5;
				row3 = 0x5;
				row4 = 0x1;	
				
				printChar(pos, row1, row2, row3, row4);		
			}
			if (charToInt == 1){
				row1 = 0x0;
				row2 = 0x1;
				row3 = 0x1;
				row4 = 0x0;	
				
				printChar(pos, row1, row2, row3, row4);		
			}
			if (charToInt == 2){
				row1 = 0x1;
				row2 = 0x1;
				row3 = 0xE;
				row4 = 0x1;	
				
				printChar(pos, row1, row2, row3, row4);		
			}
			if (charToInt == 3){
				row1 = 0x1;
				row2 = 0x1;
				row3 = 0xB;
				row4 = 0x1;	
				
				printChar(pos, row1, row2, row3, row4);		
			}
			if (charToInt == 4){
				row1 = 0x0;
				row2 = 0x5;
				row3 = 0xB;
				row4 = 0x0;	
				
				printChar(pos, row1, row2, row3, row4);		
			}
			if (charToInt == 5){
				row1 = 0x1;
				row2 = 0x4;
				row3 = 0xB;
				row4 = 0x1;
				
				printChar(pos, row1, row2, row3, row4);			
			}
			if (charToInt == 6){
				row1 = 0x1;
				row2 = 0x4;
				row3 = 0xF;
				row4 = 0x1;		
				
				printChar(pos, row1, row2, row3, row4);	
			}
			if (charToInt == 7){
				row1 = 0x1;
				row2 = 0x1;
				row3 = 0x1;
				row4 = 0x0;			
				
				printChar(pos, row1, row2, row3, row4);
			}
			if (charToInt == 8){
				row1 = 0x1;
				row2 = 0x5;
				row3 = 0xF;
				row4 = 0x1;			
				
				printChar(pos, row1, row2, row3, row4);
			}			
			if (charToInt == 9){
				row1 = 0x1;
				row2 = 0x5;
				row3 = 0xB;
				row4 = 0x0;			
				
				printChar(pos, row1, row2, row3, row4);
			}
		}
	}
}

void writeLong(long i){
	
	// Convert int to string
	char charOf_i;
	
	// Display the six least significant digits
	for(int count = 6; count > 0; count--){
		if(count != 0 && i == 0){
			break;
		}
		charOf_i = i % 10;
		writeChar(charOf_i, count);
		i = i / 10;
	}
}

long is_Primes(long i){
	long rest;
	for (long n = 2; n < i; n++){
		rest = i % n;
		if (rest == 0){
			return 0;
		}
	}
	return 1;
}

void primes(){
	long i = 1;
	while (i > 0){
		if (is_Primes(i) == 1){
			writeLong(i);
		}
		i++;
	}
}

int main(void){
	// LCD settings
	LCD_Init();

	// Lab1 part1.1
	//writeChar(6,6);
	
	// Lab1 part1.2
	//writeLong(1234567890);
	
	// Lab1 part1.3
	primes();

}