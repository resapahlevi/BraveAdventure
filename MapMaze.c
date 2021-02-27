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
#include "USART.h"

bool CheckObs(uint16_t posX,uint16_t posY ){
	if(((posX+1) <= SquareMaze) || ((posY+1) <= SquareMaze) || ((posX - 1) >= 0) || ((posY -1 ) >= 0)){
		if(isExecute == true){
			isExecute = false;
			if (headdirect.px == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX - 1][posY].isClear == false)){
					B++;
					if(B == Persquare) {
						UpdateArray((posX - 1), posY);
						B = 0;
					}
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goBack;
				}
				else {
					B = 0;
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY + 1].isClear == false)){
					L++;
					if (L == Persquare){
						UpdateArray(posX, (posY + 1));
						L = 0;
					}
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY - 1].isClear == false)){
					R++;
					if (R == Persquare){
						UpdateArray(posX, (posY - 1));
						R = 0;
					}
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX + 1][posY].isClear == false)){
					F++;
					if (F == Persquare){
						UpdateArray((posX + 1), posY);
						F = 0;
					}
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goForward;
				}
				else{
					resetcountermaze();
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goRight;
				}
				return true;
			}
			else if (headdirect.py == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY - 1].isClear == false)){
					B++;
					if( B == Persquare){
						UpdateArray(posX, (posY - 1));
						B = 0;
					}
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goBack;
				}
				else{
					B = 0;
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX - 1][posY].isClear == false)){
					L++;
					if ( L == Persquare){
						UpdateArray((posX -1), posY);
						L = 0;
					}
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX + 1][posY].isClear == false)){
					R++;
					if( R == Persquare){
						UpdateArray((posX + 1), posY);
						R = 0;
					}
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY + 1].isClear == false)){
					F++;
					if(F == Persquare){
						UpdateArray(posX, (posY + 1));
						F = 0;
					}
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goForward;
				}
				else{
					resetcountermaze();
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goRight;
				}
				return true;
			}
			else if (headdirect.mx == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX + 1][posY].isClear == false)){
					B++;
					if(B == Persquare){
						UpdateArray((posX + 1), posY);
						B = 0 ;
					}
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goBack;
				}
				else{
					B = 0;
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY - 1].isClear == false)){
					L++;
					if(L == Persquare){
						UpdateArray(posX, (posY - 1));
						L = 0;
					}
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY + 1].isClear == false)){
					R++;
					if( R == Persquare){
						UpdateArray(posX, (posY + 1));
						R = 0 ;
					}
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX - 1][posY].isClear == false)){
					F++;
					if(F == Persquare){
						UpdateArray((posX - 1), posY);
						F = 0;
					}
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goForward;
				}
				else{
					resetcountermaze();
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goRight;
				}
				return true;
			}
			else if (headdirect.my == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY + 1].isClear == false)){
					B++;
					if(B == Persquare){
						UpdateArray(posX, (posY + 1));
						B = 0;
					}
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goBack;
				}
				else{
					B = 0;
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX + 1][posY].isClear == false)){
					L++;
					if(L == Persquare){
						UpdateArray((posX + 1), posY);
						L = 0;
					}
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX - 1][posY].isClear == false)){
					R++;
					if(R == Persquare){
						UpdateArray((posX - 1), posY);
						R = 0;
					}
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY - 1].isClear == false)){
					F++;
					if(F == Persquare){
						UpdateArray(posX, (posY - 1));
						F = 0;
					}
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goForward;
				}
				else{
					resetcountermaze();
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goRight;
				}
				return true;
			}
		}
	}
	else {
		if(
			((posX+1) > SquareMaze) &
			((posY+1) > SquareMaze) &
			(headdirect.px == head) &
			(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
			(maze[posX][posY - 1].isClear == false)
			){
			DirToGo.goesto = negatifY;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posX+1) > SquareMaze) &
				((posY+1) > SquareMaze) &
				(headdirect.py == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX -1][posY].isClear == false)
				){
			DirToGo.goesto = negatifX;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posX - 1) < 0) &
				((posY+1) > SquareMaze) &
				(headdirect.mx == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX][posY - 1].isClear == false)
				){
			DirToGo.goesto = negatifY;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posX - 1) < 0) &
				((posY+1) > SquareMaze) &
				(headdirect.py == head) &
				(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
				(maze[posX + 1][posY].isClear == false)
				){
			DirToGo.goesto = positifX;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posX - 1) < 0) &
				((posY - 1) < 0) &
				(headdirect.my == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX + 1][posY].isClear == false)
				){
			DirToGo.goesto = positifX;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posX - 1) < 0) &
				((posY - 1) < 0) &
				(headdirect.mx == head) &
				(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
				(maze[posX][posY + 1].isClear == false)
				){
			DirToGo.goesto = positifY;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posX + 1) > SquareMaze) &
				((posY - 1) < 0) &
				(headdirect.px == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX][posY + 1].isClear == false)
				){
			DirToGo.goesto = positifY;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posX + 1) > SquareMaze) &
				((posY - 1) < 0) &
				(headdirect.my == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX - 1][posY].isClear == false)
				){
			DirToGo.goesto = negatifX;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posX+1) > SquareMaze) &
				(headdirect.px == head) &
				(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
				(maze[posX][posY - 1].isClear == false)
				){
			DirToGo.goesto = negatifY;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posX+1) > SquareMaze) &
				(headdirect.px == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX][posY + 1].isClear == false)
				){
			DirToGo.goesto = positifY;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posY+1) > SquareMaze) &
				(headdirect.py == head) &
				(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
				(maze[posX + 1][posY].isClear == false)
				){
			DirToGo.goesto = positifX;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posY+1) > SquareMaze) &
				(headdirect.py == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX - 1][posY].isClear == false)
				){
			DirToGo.goesto = negatifX;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posX- 1) < 0) &
				(headdirect.mx == head) &
				(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
				(maze[posX][posY + 1].isClear == false)
				){
			DirToGo.goesto = positifY;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posX- 1) < 0) &
				(headdirect.mx == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX][posY - 1].isClear == false)
				){
			DirToGo.goesto = negatifY;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else if(
				((posY- 1) < 0) &
				(headdirect.my == head) &
				(readObs(ObstacleR) == PINtoInt(ObstacleR)) &
				(maze[posX - 1][posY].isClear == false)
				){
			DirToGo.goesto = negatifX;
			DirToGo.gomotor = goRight;
			resetcountermaze();
			return true;
		}
		else if(
				((posY- 1) < 0) &
				(headdirect.my == head) &
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &
				(maze[posX + 1][posY].isClear == false)
				){
			DirToGo.goesto = positifX;
			DirToGo.gomotor = goLeft;
			resetcountermaze();
			return true;
		}
		else{
			return false;
		}
	}
	isExecute = false;
	return false;
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
			maze[c][r].isClear = false;
			maze[c][r].isDone = false;
		}
	}
}

bool TothatBox(uint16_t posX,uint16_t posY, uint16_t posXDes, uint16_t posYDes ){
	uint16_t Eclid = 999;
	if(EcluideanDist(posXDes, posYDes, posX, posY) == 0){
		if(isExecute == true){
			if (headdirect.px == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX - 1][posY].isClear == false)){
					if (EcluideanDist(posXDes, posYDes, (posX - 1), posY) <= Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goForward;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				return false;
			}
			else if (headdirect.py == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goForward;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				return false;
			}
			else if (headdirect.mx == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goForward;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				return false;
			}
			else if (headdirect.my == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) & (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) & (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) & (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) & (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goForward;
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
	if ((*(posDest + 0) == 0) && (*(posDest + 1) == 0)){
		return neither;
	}
	if( TothatBox(posX, posY, posDest[0], posDest[1]) == false){
		return false;
	}
	else return true;
}

bool BackToHome(uint16_t posX, uint16_t posY){
	if( TothatBox(posX, posY, (SquareMaze / 2), (SquareMaze / 2)) == false){
		return false;
	}
	else return true;
}

void resetcountermaze(void)
{
	F	= 0;
	R	= 0;
	L	= 0;
	B	= 0;
}

