/*
 * motorshield.h
 *
 *
 *  Author: Dennis Wildmark
 */ 


#ifndef MOTORSHIELD_H_
#define MOTORSHIELD_H_
#define CHECK_PIN		PIO_PB26_IDX
#define DIRECTION_PIN	PIO_PB27_IDX
#define PWM_PIN			PIO_PC22_IDX

void motorshield_init(void);


#endif /* MOTORSHIELD_H_ */