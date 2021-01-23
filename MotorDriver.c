/*
 * MotorDriver.c
 *
 *
 *      Author: squanixmachine
 */
#include <avr/io.h>
#include "PinDefined.h"
#include "MotorDriver.h"
#include "GeneralFunc.h"
#include <util/delay.h>
#include "MapMaze.h"

void turnright(){
	printString("Turn Right \r\n");
	MotorBlock &= ~(_BV(MotorIn1)) | ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
	MotorBlock |= _BV(MotorIn3);
	analogWrite(0x08,200);
	analogWrite(0x10,0);
	//_delay_ms(Delay_Turn);
	stops();
	//isExecute = true;
	//forward();
}

void turnleft(){
	printString("Turn Left \r \n");
	MotorBlock &= ~(_BV(MotorIn3)) | ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
	MotorBlock |= _BV(MotorIn1) ;
	analogWrite(0x10,200);
	analogWrite(0x08,0);
	stops();
}

void forward(){
	printString("Forward \r\n");
	MotorBlock &= ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
	MotorBlock |= _BV(MotorIn1) | _BV(MotorIn3) ;
	analogWrite(0x08,200);
	analogWrite(0x10,200);
	stops();
}

void bacrward(){
	printString("Backward \r\n");
	MotorBlock &= ~(_BV(MotorIn1)) | ~(_BV(MotorIn3));
	MotorBlock |= _BV(MotorIn2) | _BV(MotorIn4) ;
	analogWrite(0x08,200);
	analogWrite(0x10,200);
	stops();
}

void stops(){
  _delay_ms(Delay_Motor);
  printString("Stops Motor \r\n");
  isExecute = true;
}

void Realstops(){
	MotorBlock &= (MotorBlock & 0x00) | ~(_BV(MotorIn1)) | ~(_BV(MotorIn3)) | ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
}
