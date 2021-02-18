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
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX - 1][posY].isClear == false)){
					UpdateArray((posX - 1), posY);
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
				}
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
			}
			else if (headdirect.py == head){
				printString("Head py ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY - 1].isClear == false)){
					UpdateArray(posX, (posY - 1));
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
				}
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
			}
			else if (headdirect.mx == head){
				printString("Head mx ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX + 1][posY].isClear == false)){
					UpdateArray((posX + 1), posY);
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
				}
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
			}
			else if (headdirect.my == head){
				printString("Head my ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY + 1].isClear == false)){
					UpdateArray(posX, (posY + 1));
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goBack;
					printString(" B \r \n");
				}
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
	uint16_t  posx , posy , EuD , minEuD = SquareMaze;
	static uint16_t pos[2] = {0,0};
	for(posx = 0 ; posx < SquareMaze ; posx++){
		for(posy = 0  ; posy < SquareMaze ; posy++){
			if(maze[posx][posy].isClear == true && maze[posx][posy].isDone == false) {
				EuD = EcluideanDist(CurposX,CurposY,posx,posy);
				if(EuD < minEuD){
					pos[0] = posx;
					pos[1] = posy;
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

bool TothatBox(uint16_t posX,uint16_t posY, uint16_t posXDes, uint16_t posYDes ){
	uint16_t Eclid = 999;
	if(EcluideanDist(posXDes, posYDes, posX, posY) == 0){
		if(isExecute == true){
			printString("To That Box \r \n");
			if (headdirect.px == head){
				printString("Head px ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX - 1][posY].isClear == false)){
					if (EcluideanDist(posXDes, posYDes, (posX - 1), posY) <= Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goBack;
						printString(" B \r \n");
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goLeft;
						printString(" L ");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goRight;
						printString(" R ");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goForward;
						printString(" F \r \n");
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				return false;
			}
			else if (headdirect.py == head){
				printString("Head py ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goBack;
						printString(" B \r \n");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goLeft;
						printString(" L ");
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goRight;
						printString(" R ");
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goForward;
						printString(" F \r\n ");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				return false;
			}
			else if (headdirect.mx == head){
				printString("Head mx ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goBack;
						printString(" B \r \n");
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goLeft;
						printString(" L ");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goRight;
						printString(" R ");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goForward;
						printString(" F \r\n ");
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				return false;
			}
			else if (headdirect.my == head){
				printString("Head my ");
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goBack;
						printString(" B \r \n");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goLeft;
						printString(" L ");
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goRight;
						printString(" R ");
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goForward;
						printString(" F \r\n ");
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				return false;
			}
			else {
				DirToGo.goesto = goNull;
				DirToGo.gomotor = goBack;
				return false;
			}
			isExecute = false;
		}
		return false;
	}
	else{
		return true;
	}
}

bool FindTheDest(uint16_t posX, uint16_t posY){
	uint16_t *posDest;
	posDest = CheckMaze(posX, posY);
	if ((posDest[0] == 0) && (posDest[1] == 0)){
		return neither;
	}
	if( TothatBox(posX, posY, posDest[0], posDest[1]) == false){
		return false;
	}
	else return true;
}

bool BackToHome(uint16_t posX, uint16_t posY){
	if( TothatBox(posX, posY, SquareMaze / 2, SquareMaze / 2) == false){
		return false;
	}
	else return true;
}

