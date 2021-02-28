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

bool CheckObs(int posX,int posY ){
	/* This code to make rules when the robot reach the edge of maze
	 * 	Actually this code is so frustrating. You need to know every possible.
	 * 	What the pain is maybe this code is never execute at all, but you need to write it.
	 */
	if(									// Quadrant 1
		(posX == (SquareMaze - 1)) &&
		(posY == (SquareMaze - 1))
		){
		if(isExecute == true)
		{
			isExecute = false;
			if (
				(headdirect.py == head) &&
				(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
				(maze[posX -1][posY].isClear == false)
				){
					mazeEdge.q1py = true;
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goLeft;
					movestage = true;
					return true;
			}
			else if(
					(headdirect.px == head) &&
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX][posY - 1].isClear == false)
					){
					mazeEdge.q1px = true;
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goRight;
					movestage = true;
					return true;
			}
		}
	}
	else if(						// Quadrant 2
			(posX == 0) &&
			(posY == (SquareMaze - 1))
			){
			if(isExecute == true)
			{
				isExecute = false;
				if(
					(headdirect.mx == head) &&
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						mazeEdge.q2mx = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
					(headdirect.py == head) &&
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						mazeEdge.q2py = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goRight;
						movestage = true;
						return true;
				}
			}
		}
	else if(							//Quadrant 3
			(posX == 0) &&
			(posY == 0)
			){
			if(isExecute == true)
			{
				isExecute = false;
				if(
					(headdirect.my == head) &&
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						mazeEdge.q3my = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
						(headdirect.mx == head) &&
						(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
						(maze[posX][posY + 1].isClear == false)
						){
							mazeEdge.q3mx = true;
							DirToGo.goesto = positifY;
							DirToGo.gomotor = goRight;
							movestage = true;
							return true;
				}
		}
	}
	else if(							// Quadrant 4
			(posX == (SquareMaze - 1)) &&
			(posY == 0)
			){
			if(isExecute == true)
			{
				isExecute = false;
				if(
					(headdirect.px == head) &&
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						mazeEdge.q4px = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
					(headdirect.my == head) &&
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						mazeEdge.q4my = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goRight;
						movestage = true;
						return true;
				}
		}
	}

	/* This code is also to make rules when the robot reach the maze border.
	 * Its more complicated. Every border has three possibilities multiply by two direction, and you need defined that.
	 * And again, what the pain is this rules maybe never executed at all.
	 */
	if(
		(posX == (SquareMaze - 1))							// quadrant between 1 and 4
		){
		if(isExecute == true)
		{
			isExecute = false;
			if(headdirect.px == head)							// Just don't go forward
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						mazeEdge.q4q1 = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						mazeEdge.q4q1 = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goRight;
						movestage = true;
						return true;
				}
			}
			else if(headdirect.my == head)						// just don't go also check left side
			{
				if (
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						R++;
						if (R == Persquare){
							UpdateArray((posX - 1), posY);
							R = 0;
						}
						mazeEdge.q4q1 = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goRight;
				}
				else {
					R = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray(posX, (posY - 1));
							movestage = true;
						}
						mazeEdge.q4q1 = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goForward;
				}
				else {
					movestage = true;
				}
				return true;
			}
			else if(headdirect.py == head)						// just don't go also check right side
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						L++;
						if (L == Persquare){
							UpdateArray((posX - 1), posY);
							L = 0;
						}
						mazeEdge.q4q1 = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray(posX, (posY + 1));
							movestage = true;
						}
						mazeEdge.q4q1 = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
		}
	}
	else if(
		(posY == (SquareMaze - 1))							// quadrant between 1 and 2
		){
		if(isExecute == true)
		{
			isExecute = false;
			if(headdirect.py == head)							// Just don't go forward
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						mazeEdge.q1q2 = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						mazeEdge.q1q2 = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goRight;
						movestage = true;
						return true;
				}
			}
			else if(headdirect.px == head)						// just don't go also check left side
			{
				if (
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						R++;
						if (R == Persquare){
							UpdateArray(posX, (posY - 1));
							R = 0;
						}
						mazeEdge.q1q2 = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray((posX + 1), posY);
							movestage = true;
						}
						mazeEdge.q1q2 = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
			else if(headdirect.mx == head)						// just don't go also check right side
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						L++;
						if (L == Persquare){
							UpdateArray(posX, (posY - 1));
							L = 0;
						}
						mazeEdge.q1q2 = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray((posX - 1), posY);
							movestage = true;
						}
						mazeEdge.q1q2 = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
		}
	}
	else if(
		(posX == 0)											// quadrant between 2 and 3
		){
		if(isExecute == true)
		{
			isExecute = false;
			if(headdirect.mx == head)							// Just don't go forward
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						mazeEdge.q2q3 = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						mazeEdge.q2q3 = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goRight;
						movestage = true;
						return true;
				}
			}
			else if(headdirect.py == head)						// just don't go also check left side
			{
				if (
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						R++;
						if (R == Persquare){
							UpdateArray((posX + 1), posY);
							R = 0;
						}
						mazeEdge.q2q3 = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray(posX, (posY + 1));
							movestage = true;
						}
						mazeEdge.q2q3 = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
			else if(headdirect.my == head)						// just don't go also check right side
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						L++;
						if (L == Persquare){
							UpdateArray((posX + 1), posY);
							L = 0;
						}
						mazeEdge.q2q3 = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX][posY - 1].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray(posX, (posY - 1));
							movestage = true;
						}
						mazeEdge.q2q3 = true;
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
		}
	}
	else if(
		(posY == 0)											// quadrant between 3 and 4
		){
		if(isExecute == true)
		{
			isExecute = false;
			if(headdirect.my == head)							// Just don't go forward
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						mazeEdge.q3q4 = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goLeft;
						movestage = true;
						return true;
				}
				else if(
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						mazeEdge.q3q4 = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goRight;
						movestage = true;
						return true;
				}
			}
			else if(headdirect.mx == head)						// just don't go also check left side
			{
				if (
					(readObs(ObstacleR) == PINtoInt(ObstacleR)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						R++;
						if (R == Persquare){
							UpdateArray((posX + 1), posY);
							R = 0;
						}
						mazeEdge.q3q4 = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goRight;
				}
				else{
					R = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX - 1][posY].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray((posX - 1), posY);
							movestage = true;
						}
						mazeEdge.q3q4 = true;
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
			else if(headdirect.px == head)						// just don't go also check right side
			{
				if (
					(readObs(ObstacleL) == PINtoInt(ObstacleL)) &&
					(maze[posX][posY + 1].isClear == false)
					){
						L++;
						if (L == Persquare){
							UpdateArray(posX, (posY + 1));
							L = 0;
						}
						mazeEdge.q3q4 = true;
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goLeft;
				}
				else{
					L = 0;
				}
				if (
					(readObs(ObstacleF0) == PINtoInt(ObstacleF0)) &&
					(maze[posX + 1][posY].isClear == false)
					){
						F++;
						if( F == Persquare){
							UpdateArray((posX + 1), posY);
							movestage = true;
						}
						mazeEdge.q3q4 = true;
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
				}
				return true;
			}
		}
	}
	/*
	 * This code give regular rules to the robot.
	 * Actually it's simple than the edge and border code.
	 */
	else if(
			((posX) < SquareMaze) &&
			((posY) < SquareMaze) &&
			((posX) > 0) &&
			((posY) > 0)
			){
		if(isExecute == true)
		{
			isExecute = false;
			if (headdirect.px == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX - 1][posY].isClear == false)){
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
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX][posY + 1].isClear == false)){
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
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX][posY - 1].isClear == false)){
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
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX + 1][posY].isClear == false)){
					F++;
					if (F == Persquare){
						UpdateArray((posX + 1), posY);
						movestage = true;
					}
					DirToGo.goesto = positifX;
					DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
					return true;
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.gomotor = goRight;
				}
				return true;
			}
			else if (headdirect.py == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX][posY - 1].isClear == false)){
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
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX - 1][posY].isClear == false)){
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
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX + 1][posY].isClear == false)){
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
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX][posY + 1].isClear == false)){
					F++;
					if(F == Persquare){
						UpdateArray(posX, (posY + 1));
						movestage = true;
					}
					DirToGo.goesto = positifY;
					DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
					return true;
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.gomotor = goRight;
				}
				return true;
			}
			else if (headdirect.mx == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX + 1][posY].isClear == false)){
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
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX][posY - 1].isClear == false)){
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
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX][posY + 1].isClear == false)){
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
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX - 1][posY].isClear == false)){
					F++;
					if(F == Persquare){
						UpdateArray((posX - 1), posY);
						movestage = true;
					}
					DirToGo.goesto = negatifX;
					DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
					return true;
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.gomotor = goRight;
				}
				return true;
			}
			else if (headdirect.my == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX][posY + 1].isClear == false)){
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
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX + 1][posY].isClear == false)){
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
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX - 1][posY].isClear == false)){
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
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX][posY - 1].isClear == false)){
					F++;
					if(F == Persquare){
						UpdateArray(posX, (posY - 1));
						movestage = true;
					}
					DirToGo.goesto = negatifY;
					DirToGo.gomotor = goForward;
				}
				else{
					movestage = true;
					return true;
				}
				if(readObs(ObstacleF1) != PINtoInt(ObstacleF1)){
					DirToGo.gomotor = goLeft;
				}
				if(readObs(ObstacleF2) != PINtoInt(ObstacleF2)){
					DirToGo.gomotor = goRight;
				}
				return true;
			}
		}
	}
	isExecute = false;
	return false;
}

bool UpdateArray(int posX, int posY) {
	return maze[posX][posY].isClear = true ;
}

uint16_t * CheckMaze(int CurposX, int CurposY){
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

uint16_t EcluideanDist(int CurposX, int CurposY, int posX, int posY){
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
/*
 * This give a rules to guide the robot to go some coordinate. This maybe happen when robot reach dead-end way.
 * In this rules you need to know at least two point, where you are now and where you want to.
 *
 * This rules will compare the weight point of current coordinate and destination coordinate using ecluidian distance.
 */
bool TothatBox(int posX,int posY, int posXDes, int posYDes ){
	uint16_t Eclid = 999;
	if(EcluideanDist(posXDes, posYDes, posX, posY) == 0){
		if(isExecute == true){
			if (headdirect.px == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX - 1][posY].isClear == false)){
					if (EcluideanDist(posXDes, posYDes, (posX - 1), posY) <= Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goForward;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				return false;
			}
			else if (headdirect.py == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goForward;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				return false;
			}
			else if (headdirect.mx == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX][posY - 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY - 1)) < Eclid){
						DirToGo.goesto = negatifY;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY - 1));
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goForward;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				return false;
			}
			else if (headdirect.my == head){
				if((readObs(ObstacleB0) == PINtoInt(ObstacleB0)) && (maze[posX][posY + 1].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, posX, (posY + 1)) < Eclid){
						DirToGo.goesto = positifY;
						DirToGo.gomotor = goBack;
						Eclid = EcluideanDist(posXDes, posYDes, posX, (posY + 1));
					}
				}
				if((readObs(ObstacleL) == PINtoInt(ObstacleL)) && (maze[posX + 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX + 1), posY) < Eclid){
						DirToGo.goesto = positifX;
						DirToGo.gomotor = goLeft;
						Eclid = EcluideanDist(posXDes, posYDes, (posX + 1), posY);
					}
				}
				if((readObs(ObstacleR) == PINtoInt(ObstacleR)) && (maze[posX - 1][posY].isClear == false)){
					if( EcluideanDist(posXDes, posYDes, (posX - 1), posY) < Eclid){
						DirToGo.goesto = negatifX;
						DirToGo.gomotor = goRight;
						Eclid = EcluideanDist(posXDes, posYDes, (posX - 1), posY);
					}
				}
				if((readObs(ObstacleF0) == PINtoInt(ObstacleF0)) && (maze[posX][posY - 1].isClear == false)){
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

bool FindTheDest(int posX, int posY){
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

bool BackToHome(int posX, int posY){
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

