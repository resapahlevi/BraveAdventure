/*
 * MapMaze.h
 *
 *
 *      Author: squanixmachine
 */

#include "GeneralFunc.h"

#ifndef MAPMAZE_H_
#define MAPMAZE_H_

#define SquareMaze 61
#define Persquare 20000

typedef enum {head, tail} direct;

struct ArrayProp {
	bool isClear, isDone;
} ArrayProp;

struct direction {
	direct px, py, mx, my;
}direction;

struct mazeedge{
	bool q1py, q1px, q2py, q2mx, q3my, q3mx, q4px, q4my, q1q2, q2q3, q3q4, q4q1;
}mazeedge;

struct CurrentPos {
	int CurX , CurY ;
}CurrentPos;

bool isExecute;
bool imstuck;
bool movestage;
uint16_t F, L, R, B;

struct ArrayProp maze[SquareMaze][SquareMaze];
struct direction headdirect;
struct mazeedge mazeEdge;

bool CheckObs(int posX,int posY);
bool UpdateArray(int posX, int posY);
uint16_t * CheckMaze(int CurposX, int CurposY);
uint16_t EcluideanDist(int CurposX, int CurposY, int posX, int posY);
void initMaze();
bool FindTheDest(int posX, int posY);
bool BackToHome(int posX, int posY);
void resetcountermaze(void);

#endif /* MAPMAZE_H_ */
