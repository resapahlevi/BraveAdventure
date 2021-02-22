/*
 * MotorDriver.h
 *
 *
 *      Author: squanixmachine
 */

#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#define Delay_Motor 1300
#define Delay_Turn 1500
#define MotorSpeedRunR 130
#define MotorSpeedRunL 150
#define MotorSpeedTurn 170
#define MotorSpeedStop 0

void turnright();
void turnleft();
void forward();
void bacrward();
void stops();
void Realstops();

#endif /* MOTORDRIVER_H_ */
