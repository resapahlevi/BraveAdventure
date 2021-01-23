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

struct StateRobo {state stateRobo;} StateRobo;

void FiniteState(state currentState);

#endif /* FSM_H_ */
