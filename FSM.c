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

void FiniteState(state currentState){

	switch(currentState)
	{
		case init :
			CheckObs(CurrentPos.CurX, CurrentPos.CurY);
			WhereYouGo();
			StateRobo.stateRobo = lookaround;
			printString("init \r \n");
			break;
		case lookaround :
			if(CheckObs(CurrentPos.CurX, CurrentPos.CurY) == true){
				StateRobo.stateRobo = step;
				printString("Lookaround \r \n");
			}
			else{
				StateRobo.stateRobo = endway;
			}
			break;
		case step :
			WhereYouGo();
			printString("Step \r \n");
			StateRobo.stateRobo = lookaround;
			break;
		case endway :

			StateRobo.stateRobo = init;
			break;
		case backhome :
			/*
			 * This is very complicated, return to home position
			 *
			 */
			StateRobo.stateRobo = null;
			break;
		case null :

			break;
	}

}


