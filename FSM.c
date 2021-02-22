/*
 * FSM.c
 *
 *
 *      Author: squanixmachine
 */

/*
 * Description :
 *
 * There is four state
 * 		1. Check the obstacle as 0
 * 		2. Step as 1
 * 		3. Are We Done ? as 2
 */

#include <avr/io.h>
#include "FSM.h"
#include "MapMaze.h"
#include "Obs.h"
#include "USART.h"
#include "util/delay.h"
#include "MotorDriver.h"

void FiniteState(state currentState){

	switch(currentState)
	{
		case init :
			CheckObs(CurrentPos.CurX, CurrentPos.CurY);
			WhereYouGo();
			StateRobo.stateRobo = lookaround;
			printString("init \r \n");
			CurStateRobo.stateRobo = init;
			break;
		case lookaround :
			if(CheckObs(CurrentPos.CurX, CurrentPos.CurY) == true){
				StateRobo.stateRobo = step;
				printString("Lookaround \r \n");
			}
			else{
				StateRobo.stateRobo = endway;
			}
			CurStateRobo.stateRobo = lookaround;
			break;
		case step :
			WhereYouGo();
			printString("Step \r \n");
			if(CurStateRobo.stateRobo == lookaround) StateRobo.stateRobo = lookaround;
			if(CurStateRobo.stateRobo == endway) StateRobo.stateRobo = endway;
			if(CurStateRobo.stateRobo == backhome) StateRobo.stateRobo = backhome;
			CurStateRobo.stateRobo = step;
			break;
		case endway :
			imstuck = FindTheDest(CurrentPos.CurX, CurrentPos.CurY);
			if (imstuck == 5){
				printString("FALSE");
				StateRobo.stateRobo = step;
			}
			else if (imstuck == 7){
				printString("TRUE");
				StateRobo.stateRobo = lookaround;
			}
			else if (imstuck == 3){
				StateRobo.stateRobo = backhome;
				printString("NEITHER");
			}
			CurStateRobo.stateRobo = endway;
			break;
		case backhome :
			/*
			 * This is very complicated, return to home position
			 *
			 */
			if (BackToHome(CurrentPos.CurX, CurrentPos.CurY) == false){
				StateRobo.stateRobo = step;
			}
			else{
				StateRobo.stateRobo = null;
			}
			CurStateRobo.stateRobo = backhome;
			break;
		case null :
			Realstops();
			StateRobo.stateRobo = null;
			break;
	}

}


