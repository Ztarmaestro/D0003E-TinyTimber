


#ifndef GUI_H_
#define GUI_H_
#include "TinyTimber.h"

typedef struct{
	Object super;
	int leftvalue;
	int rightvalue;

}GUI;

#define initGUI(leftvalue, rightvalue){initObject(), leftvalue, rightvalue}

void writeChar(char ch, int pos);
void printAt(long num, int pos);

#endif /* GUI_H_ */