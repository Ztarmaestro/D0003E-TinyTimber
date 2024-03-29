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
char *arg = 0;

pthread_t TrafThread;
pthread_t LightThread;
pthread_t GUIThread;
sem_t GuiSem;


int comfile;

int mutex = 0;


void *lights(void *arg);
void *GUI(void *arg);
void initCom1(){
	struct termios Options;
	comfile = open("/dev/ttyS0", O_RDWR |O_NOCTTY);
	
	/* Get default for port */
	tcgetattr(comfile, &Options);
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
	tcsetattr(comfile,TCSANOW,&Options);
	tcflush(comfile, TCIFLUSH);
	
}

void comfileWrite(uint8_t c){
	mutex = 1;
	write(comfile, &c, 1);
	mutex = 0;
	sem_post(&GuiSem);
	
}

void *lights(void *arg){
	while (1){
		uint8_t filebuffer;
		read(comfile, &filebuffer, 1);
		if (filebuffer == 0xA){
			//If both lights are red!
			northLightG = 0;
			southLightG = 0;
		}
		if (filebuffer == 0x9){
			//If northLight is green and southLight is red 
			northQ -= 1;
			comfileWrite(0x2);
			northLightG = 0;
			southLightG = 0;
		}
		if (filebuffer == 0x6){
			//If southLight is green and northLight is red
			southQ -= 1;
			comfileWrite(0x8);
			northLightG = 0;
			southLightG = 0;
		}
	}
}

void cars(void *a){
	while(1){
		uint8_t keyPressed = getchar();
		if (keyPressed == 's'){
			southQ +=1;
			//Add 1 to south Q
			comfileWrite(0x4);
			//Write out a car on screen
		} else if (keyPressed == 'n'){
			northQ +=1;
			//Add 1 to north Q
			comfileWrite(0x1);
			//Write out a car on screen
		}
	}
}

void *GUI(void *arg){
	while (1){
		//run sem on gui
		sem_wait(&GuiSem);
		//GUI ART
		mutex = 1;

		printf("%d North Light	   South Light	%d\n",northLightG,southLightG);
		printf("%d North Que	South Que %d\n",northQ,southQ);
		mutex = 0;		
	}
}

main(){
	initCom1();
	pthread_create(&TrafThread, NULL, lights, &arg);
	pthread_create(&GUIThread,NULL,GUI, &arg);
	sem_init(&GuiSem, 0, 0);
	//Start treads & init sem
	
	cars(NULL);
}