/*
 * GeneralFunc.h
 *
 *
 *      Author: squanixmachine
 */

#ifndef GENERALFUNC_H_
#define GENERALFUNC_H_

typedef enum { false , true , neither } bool;


void analogWrite(uint8_t pin, uint8_t val);
void pwm_init();
uint16_t analogRead(uint8_t port);
void adc_init();
uint8_t mapping(uint16_t val);

#endif /* GENERALFUNC_H_ */
