/*
 * MapMaze.h
 *
 *
 *      Author: squanixmachine
 */

#include "GeneralFunc.h"

#ifndef MAPMAZE_H_
#define MAPMAZE_H_

#define SquareMaze 60
#define Persquare 1000

typedef enum {head, tail} direct;

struct ArrayProp {
	bool isClear, isDone;
} ArrayProp;

struct direction {
	direct px, py, mx, my;
}direction;

struct CurrentPos {
	uint16_t CurX , CurY ;
}CurrentPos;

bool isExecute;
bool imstuck;
uint16_t F, L, R, B;

struct ArrayProp maze[SquareMaze][SquareMaze];
struct direction headdirect;

bool CheckObs(uint16_t posX,uint16_t posY);
bool UpdateArray(uint16_t posX, uint16_t posY);
uint16_t * CheckMaze(uint16_t CurposX, uint16_t CurposY);
uint16_t EcluideanDist(uint16_t CurposX, uint16_t CurposY, uint16_t posX, uint16_t posY);
void initMaze();
bool FindTheDest(uint16_t posX, uint16_t posY);
bool BackToHome(uint16_t posX, uint16_t posY);

#endif /* MAPMAZE_H_ */
