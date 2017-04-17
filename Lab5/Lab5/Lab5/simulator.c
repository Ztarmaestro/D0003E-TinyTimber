/*
 * simulator.c
 *
 * Created: 2017-04-14 15:40:33
 *  Author: jesgla-2
 */ 
#include <errno.h>      
#include <stdint.h>    
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     
#include <fcntl.h>      
#include <termios.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>		
#include <semaphore.h>
#include <termios.h>
#include <sys/types.h>

int northQ=0;
int southQ=0;
int northLightG=0;
int southLightG=0;

int comfile;

int mutex = 0;

void initCom1(){
	Struct termios Options;
	comfile = open("/dev/ttyS0", O_RDWR |O_NOCTTY);
	
	/* Get default for port */
	tcgetattr(PortFile, &Options);
	/*Set baud rate in and out*/
	cfsetispeed(&Options, B9600);
	cfsetospeed(&Options, B9600);
	/* 8 char enable recieve baud 9600, local*/
	Options.c_cflag = CS8 | B9600 | CREAD | CLOCAL;
	/* Feedback loop "error" disabled */
	Options.c_lflag &=~(ICANON | ECHO) ;
	/* wait untill atleast one char recieved */
	Options.c_cc[VMIN] = 1;
	/* set new settings */
	tcsetattr(comFile,TCSANOW,&Options);
	tcflush(PortFile, TCIFLUSH);
	
}

void comfileWrite(uint8_t c){
	mutex = 1;
	write(comfile, &c, 1);
	mutex = 0;
	
}

void lights(){
	while (){
		uint8_t filebuffer;
		read(comfile, &filebuffer, 1);
		if (filebuffer ==){
			//If both lights are red!
			northLightG = 0;
			southLightG = 0;
		}
		if (filebuffer ==){
			//If northLight is green and southLight is red 
			northQ -= 1;
			comfileWrite(/**/);
			northLightG = 0;
			southLightG = 0;
		}
		if (filebuffer ==){
			southQ -= 1
			comfileWrite(/**/);
			northLightG = 0;
			southLightG = 0;
		}
	}
}

void cars(){
	while(1){
		uint8_t keyPressed = getChar();
		if (keyPressed == "s"){
			southQ +=1;
			//Add 1 to south Q
			comfileWrite(/**/);
			//Write out a car on screen
		} else if (keyPressed == "n"){
			northQ +=1;
			//Add 1 to north Q
			comfileWrite(/**/);
			//Write out a car on screen
		}
	}
}

void *GUI(void *arg){
	while (){
	}
}

void main(){
	initCom1();
}