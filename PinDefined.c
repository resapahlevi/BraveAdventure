/*
 * PinDefined.c
 *
 *    Author: squanixmachine
 */

#include <avr/io.h>
#include "PinDefined.h"

void MotorPinInit(){
	DataDirMotor &= 0x00;
	DataDirMotor |= _BV(MotorIn1) | _BV(MotorIn2) | _BV(MotorIn3) | _BV(MotorIn4); // set as output set as 1
}


void ObstacleInit(){
	DataDirObs &= (DataDirObs & 0x00) | ~(_BV(ObstacleF0)) | ~(_BV(ObstacleR)) | ~(_BV(ObstacleL)) | ~(_BV(ObstacleB0)) | ~(_BV(ObstacleF1)) | ~(_BV(ObstacleF2)); // set as input set as 0
	PORTC |= _BV(ObstacleF0) | _BV(ObstacleF1) | _BV(ObstacleF2) | _BV(ObstacleR) | _BV(ObstacleL) | _BV(ObstacleB0) ; // set pull up set as 1
}

void ExtInit(){
	DDRC |= _BV(DDC6);
}
