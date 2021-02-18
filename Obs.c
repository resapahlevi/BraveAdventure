/*
 * Obs.c
 *
 *  Created on: Jan 1, 2021
 *      Author: squanixmachine
 */
#include <avr/io.h>
#include "PinDefined.h"
#include "GeneralFunc.h"
#include "Obs.h"
#include "MapMaze.h"
#include "MotorDriver.h"

uint8_t readObs(uint8_t ObsPin){
	return (ObsBlock & (1 << ObsPin));
}

uint8_t PINtoInt(uint8_t Pin){
	return (1 << Pin);
}
uint8_t WhereYouGo(){
	if(isExecute == false){
		printString("WhereYouGo : ");
		if (DirToGo.goesto == positifX){
			headdirect.px = head;
			headdirect.py = tail;
			headdirect.mx = tail;
			headdirect.my = tail;
			CurrentPos.CurX = CurrentPos.CurX + 1 ;
		}
		else if (DirToGo.goesto == positifY){
			headdirect.px = tail;
			headdirect.py = head;
			headdirect.mx = tail;
			headdirect.my = tail;
			CurrentPos.CurY = CurrentPos.CurY + 1 ;
		}
		else if (DirToGo.goesto == negatifX){
			headdirect.px = tail;
			headdirect.py = tail;
			headdirect.mx = head;
			headdirect.my = tail;
			CurrentPos.CurX = CurrentPos.CurX - 1 ;
		}
		else if (DirToGo.goesto == negatifY){
			headdirect.px = tail;
			headdirect.py = tail;
			headdirect.mx = tail;
			headdirect.my = head;
			CurrentPos.CurY = CurrentPos.CurY - 1 ;
		}
		else {
			headdirect.px = tail;
			headdirect.py = tail;
			headdirect.mx = tail;
			headdirect.my = tail;
		}

		if(DirToGo.gomotor == goForward){
			forward();
		}
		if(DirToGo.gomotor == goLeft){
			turnleft();
		}
		if(DirToGo.gomotor == goRight){
			turnright();
		}
		if(DirToGo.gomotor == goBack){
			bacrward();
		}
		if(DirToGo.gomotor == goNull){
			Realstops();
		}

		DirToGo.gomotor = goNull;
	}
	return true;
}
