/*
 * MapMaze.h
 *
 *
 *      Author: squanixmachine
 */

#include "GeneralFunc.h"

#ifndef MAPMAZE_H_
#define MAPMAZE_H_

#define SquareMaze 36

typedef enum {head, tail} direct;

struct ArrayProp {
	bool px, py, mx, my, isClear, isDone;
} ArrayProp;

struct direction {
	direct px, py, mx, my;
}direction;

struct CurrentPos {
	uint16_t CurX , CurY ;
}CurrentPos;

bool isExecute;

struct ArrayProp maze[SquareMaze][SquareMaze];
struct direction headdirect;

bool CheckObs(uint16_t posX,uint16_t posY);
uint8_t UpdateArray(uint16_t posX, uint16_t posY);
uint16_t * CheckMaze(uint16_t CurposX, uint16_t CurposY);
uint16_t EcluideanDist(uint16_t CurposX, uint16_t CurposY, uint16_t posX, uint16_t posY);
void initMaze();
bool FindTheDest(uint16_t posX, uint16_t posY);

#endif /* MAPMAZE_H_ */
