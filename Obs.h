/*
 * Obs.h
 *
 *  Created on: Jan 1, 2021
 *      Author: squanixmachine
 */

#ifndef OBS_H_
#define OBS_H_

typedef enum {positifX, positifY, negatifX, negatifY, goNull} Goesto;
typedef enum {goForward, goRight, goLeft, goBack, motorNull} DirectMotor;

struct DirToGo {
	Goesto goesto;
	DirectMotor gomotor;
} DirToGo;

uint8_t readObs(uint8_t ObsPin);
uint8_t PINtoInt(uint8_t Pin);
uint8_t WhereYouGo();

#endif /* OBS_H_ */
