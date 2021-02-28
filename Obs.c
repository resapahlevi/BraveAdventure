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
#include "USART.h"

uint8_t readObs(uint8_t ObsPin){
	return (ObsBlock & (1 << ObsPin));
}

uint8_t PINtoInt(uint8_t Pin){
	return (1 << Pin);
}
uint8_t WhereYouGo(){
	if(isExecute == false){
		if (DirToGo.goesto == positifX){
			headdirect.px = head;
			headdirect.py = tail;
			headdirect.mx = tail;
			headdirect.my = tail;
			if(movestage == true){
				CurrentPos.CurX = CurrentPos.CurX + 1 ;
				resetcountermaze();
				movestage = false;
			}
		}
		else if (DirToGo.goesto == positifY){
			headdirect.px = tail;
			headdirect.py = head;
			headdirect.mx = tail;
			headdirect.my = tail;
			if(movestage == true){
				CurrentPos.CurY = CurrentPos.CurY + 1 ;
				resetcountermaze();
				movestage = false;
			}
		}
		else if (DirToGo.goesto == negatifX){
			headdirect.px = tail;
			headdirect.py = tail;
			headdirect.mx = head;
			headdirect.my = tail;
			if(movestage == true){
				CurrentPos.CurX = CurrentPos.CurX - 1 ;
				resetcountermaze();
				movestage = false;
			}
		}
		else if (DirToGo.goesto == negatifY){
			headdirect.px = tail;
			headdirect.py = tail;
			headdirect.mx = tail;
			headdirect.my = head;
			if(movestage == true){
				CurrentPos.CurY = CurrentPos.CurY - 1 ;
				resetcountermaze();
				movestage = false;
			}
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
		if(DirToGo.gomotor == motorNull){
			Realstops();
		}

		DirToGo.gomotor = goNull;
	}
	return true;
}
