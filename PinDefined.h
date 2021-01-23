/*
 * PinDefined.h
 *
 *
 *      Author: squani2machine
 */

#ifndef PINDEFINED_H_
#define PINDEFINED_H_

/*
 * Description and defined pin for the robot
 *
 */
#define MotorBlock	PINA
#define EncBlock	2
#define ObsBlock	PINC

#define DataDirMotor	DDRA
#define MotorPWMA	PH3
#define MotorIn1	PA0 // OC4A
#define MotorIn2	PA1 // OC4B
#define MotorIn3	PA2 // OC4C
#define MotorIn4	PA3 // OC2B
#define MotorPWMB	PH4

#define EncoderA 	2
#define EncoderB 	2
#define DataDirObs	DDRC
#define ObstacleF0	PC0
#define ObstacleF1	PF1 // Not in Use
#define ObstacleL	PC1
#define ObstacleR	PC2
#define ObstacleB0	PC3
#define ObstacleB1	PF5 // Not in Use

/*
 * Description and defined pin for the 10-dof Sensor
 */

#define GY_SDA 		PD1
#define GY_SCL		PD0
#define GY_FSYNC	2
#define GY_INT		2

/*
 * Description and defined pin for the LCD
 */

#define LCD_SDA		PD1
#define LCD_SCL		PD0

/*
 * Description and defined pin for e2ternal purpose : relay
 */

#define Ext_t		PC6

void MotorPinInit();
void ObstacleInit();
void ExtInit();
void PWMMotorInit();

#endif /* PINDEFINED_H_ */
