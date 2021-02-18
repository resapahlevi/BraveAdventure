/*
 * FSM.h
 *
 *  Created on: Jan 1, 2021
 *      Author: squanixmachine
 */

#include "GeneralFunc.h"

#ifndef FSM_H_
#define FSM_H_

typedef enum {
	init , lookaround , step , endway , backhome, null
} state;

uint16_t posDes;

struct StateRobo {state stateRobo;} StateRobo;
struct CurStateRobo {state stateRobo;} CurStateRobo;

void FiniteState(state currentState);

#endif /* FSM_H_ */
