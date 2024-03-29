#include "TinyTimber.h"
#include "joystick.h"

#ifndef GUI_H_
#define GUI_H_

typedef struct{
	Object super;
	int leftvalue;
	int rightvalue;

}GUI;

#define initGUI(leftvalue, rightvalue){initObject(), leftvalue, rightvalue}

void writeChar(char ch, int pos);
void printAt(long num, int pos);

#endif /* GUI_H_ */