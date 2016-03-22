/*
 * task_reg.h
 *
 *
 *  Author: Dennis Wildmark, Olle Casperson
 */ 


#ifndef TASK_REG_H_
#define TASK_REG_H_

#define OFFSET 500

void task_reg(void *pvParameters);
uint16_t conv_adc_to_dist(uint16_t invalue);
uint16_t calc_dist(uint16_t adcvalue);
void update_vars(int16_t new_error, uint16_t new_pwm, uint16_t new_dist);
void regulate_P(uint16_t adcvalue);
void regulate_PID(uint16_t adcvalue);
uint16_t filter_adc(uint16_t invalue);

#endif /* TASK_REG_H_ */