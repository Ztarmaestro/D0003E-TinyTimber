/*
 * GUI.h
 *
 * Created: 2017-02-28 13:17:23
 *  Author: jespe
 */ 


#ifndef GUI_H_
#define GUI_H_

typedef struct{
	Object super;
	int leftvalue;
	int rightvalue;

}GUI;

#define initGUI(leftvalue, rightvalue){initObject(), leftvalue, rightvalue}


#endif /* GUI_H_ */