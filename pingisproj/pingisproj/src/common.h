/*
 * common.h
 *
 * Created: 2016-03-12 18:07:25
 *  Author: Spellabbet
 */ 


#ifndef COMMON_H_
#define COMMON_H_

extern float k_prop;
extern float k_int;
extern float k_deriv;
extern uint16_t setpoint;
extern uint16_t periodicity;
extern uint16_t conv_arr[100];
extern uint16_t testval;

extern uint16_t distance_val;
extern uint16_t pwm_val;
extern int16_t error_val;
extern xSemaphoreHandle semph;

#endif /* COMMON_H_ */