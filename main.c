/*
 * main.c
 *
 *
 *      Author: squanixmachine
 *
 *      This robot was dedicated to explore the unknown area. The algorithm used 2D diagram to mapping the area.
 */
#include <avr/io.h>
#include "PinDefined.h"
#include "FSM.h"
#include "MapMaze.h"
#include "GeneralFunc.h"
#include "USART.h"
#include "Obs.h"
#include <util/delay.h>


void initRobot(){
	StateRobo.stateRobo 	= init;
	CurStateRobo.stateRobo 	= init;
	CurrentPos.CurX 		= SquareMaze / 2;
	CurrentPos.CurY 		= SquareMaze / 2;
	DirToGo.goesto 			= positifX;
	DirToGo.gomotor 		= goForward;
	headdirect.px 			= head;
	headdirect.py 			= tail;
	headdirect.mx 			= tail;
	headdirect.my 			= tail;
	isExecute 				= true;
	F						= 0;
	R						= 0;
	L						= 0;
	B						= 0;
}

int main(){
	initRobot();
	initMaze();
	MotorPinInit();
	ObstacleInit();
	pwm_init();
	adc_init();
	initUSART();

	while(1){
		FiniteState(StateRobo.stateRobo);
	}

	return 0;
}
