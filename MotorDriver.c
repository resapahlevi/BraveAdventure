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
//#include "USART.h"

void turnright(){
	MotorBlock &= ~(_BV(MotorIn1)) | ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
	MotorBlock |= _BV(MotorIn3);
	analogWrite(0x08,MotorSpeedTurn);
	analogWrite(0x10,MotorSpeedStop);
	//_delay_ms(Delay_Turn);
	stops();
}

void turnleft(){
	MotorBlock &= ~(_BV(MotorIn3)) | ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
	MotorBlock |= _BV(MotorIn1) ;
	analogWrite(0x10,MotorSpeedTurn);
	analogWrite(0x08,MotorSpeedStop);
	//_delay_ms(Delay_Turn);
	stops();
}

void forward(){
	MotorBlock &= ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
	MotorBlock |= _BV(MotorIn1) | _BV(MotorIn3) ;
	analogWrite(0x08,MotorSpeedRunR);
	analogWrite(0x10,MotorSpeedRunL);
	//_delay_ms(Delay_Motor);
	stops();
}

void bacrward(){
	MotorBlock &= ~(_BV(MotorIn1)) | ~(_BV(MotorIn3));
	MotorBlock |= _BV(MotorIn2) | _BV(MotorIn4) ;
	analogWrite(0x08,MotorSpeedRunR);
	analogWrite(0x10,MotorSpeedRunL);
	//_delay_ms(Delay_Motor);
	stops();
}

void stops(){
  isExecute = true;
}

void Realstops(){
	MotorBlock &= (MotorBlock & 0x00) | ~(_BV(MotorIn1)) | ~(_BV(MotorIn3)) | ~(_BV(MotorIn2)) | ~(_BV(MotorIn4));
}
