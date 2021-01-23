/*
 * MapMaze.c
 *
 *
 *      Author: squanixmachine
 */
#include <avr/io.h>
#include "MapMaze.h"
#include "PinDefined.h"
#include "Obs.h"
#include <math.h>

bool CheckObs(uint16_t posX,uint16_t posY ){
	if(((posX+1) <= SquareMaze) & ((posY+1) <= SquareMaze)){
		if(isExecute == true){
			printString("CheckOBS \r \n");
			if (headdirect.px == head){
				printString("Head px ");
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY + 1].isClear == false)){
					UpdateArray(posX, (posY + 1));
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goLeft;
					printString(" L ");
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY - 1].isClear == false)){
					UpdateArray(posX, (posY - 1));
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goRight;
					printString(" R ");
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX + 1][posY].isClear == false)){
					UpdateArray((posX + 1), posY);
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goForward;
					printString(" F \r \n");
				}
				else{
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
					return false;
				}
			}
			else if (headdirect.py == head){
				printString("Head py ");
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX - 1][posY].isClear == false)){
					UpdateArray((posX -1), posY);
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goLeft;
					printString(" L ");
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX + 1][posY].isClear == false)){
					UpdateArray((posX + 1), posY);
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goRight;
					printString(" R ");
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY + 1].isClear == false)){
					UpdateArray(posX, (posY + 1));
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goForward;
					printString(" F \r\n ");
				}
				else{
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
					return false;
				}
			}
			else if (headdirect.mx == head){
				printString("Head mx ");
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY - 1].isClear == false)){
					UpdateArray(posX, (posY - 1));
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goLeft;
					printString(" L ");
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY + 1].isClear == false)){
					UpdateArray(posX, (posY + 1));
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goRight;
					printString(" R ");
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX - 1][posY].isClear == false)){
					UpdateArray((posX - 1), posY);
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goForward;
					printString(" F \r\n ");
				}
				else{
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
					return false;
				}
			}
			else if (headdirect.my == head){
				printString("Head my ");
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX + 1][posY].isClear == false)){
					UpdateArray((posX + 1), posY);
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goLeft;
					printString(" L ");
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX - 1][posY].isClear == false)){
					UpdateArray((posX - 1), posY);
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goRight;
					printString(" R ");
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY - 1].isClear == false)){
					UpdateArray(posX, (posY - 1));
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goForward;
					printString(" F \r\n ");
				}
				else{
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
					return false;
				}
			}
			else {
				DirToGo.goesto = goNull;
				DirToGo.gomotor = goBack;
				return false;
			}
			isExecute = false;
		}
		return true;
	}
	else {
		DirToGo.goesto = goNull;
		DirToGo.gomotor = goNull;
		return false;
	}
}

bool UpdateArray(uint16_t posX, uint16_t posY) {
	return maze[posX][posY].isClear = true ;
}

uint16_t * CheckMaze(uint16_t CurposX, uint16_t CurposY){
	uint16_t  c , r , EuD , minEuD = SquareMaze;
	static uint16_t pos[2];
	for(c = 0 ; c < SquareMaze ; c++){
		for(r = 0 ; r < SquareMaze ; r++){
			if(maze[c][r].isClear == true && maze[c][r].isDone == false) {
				EuD = EcluideanDist(CurposX,CurposY,c,r);
				if(EuD < minEuD){
					pos[0] = c;
					pos[1] = r;
					minEuD = EuD;
				}
			}
		}
	}
	return pos;
}

uint16_t EcluideanDist(uint16_t CurposX, uint16_t CurposY, uint16_t posX, uint16_t posY){
	uint16_t d;
	d = sqrt(pow((CurposX - posX) , 2) + pow((CurposY - posY), 2));
	return d;
}

void initMaze(){
	uint16_t c , r ;
	for(c = 0 ; c < SquareMaze ; c++){
		for(r = 0 ; r < SquareMaze ; r++){
			maze[c][r].px = false;
			maze[c][r].py = false;
			maze[c][r].mx = false;
			maze[c][r].my = false;
			maze[c][r].isClear = false;
			maze[c][r].isDone = false;
		}
	}
}
