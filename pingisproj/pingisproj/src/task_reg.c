/*
 * task_reg.c
 *
 * Created: 2016-03-12 17:55:13
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "common.h"
#include "pwm_func.h"
#include "task_reg.h"

static int integ = 0;
static int derivate = 0;
static int olderr = 0;


void task_reg(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = periodicity;
	
	xLastWakeTime = xTaskGetTickCount();
	
	uint16_t adc_val;
// 	uint16_t distance;
// 	int16_t newerr;
// 	uint16_t offset = 500;
// 	uint16_t output;
	
	while(1) {
		
		adc_start(ADC);
		while((adc_get_status(ADC) & 0x1<<24)==0);
		adc_val = adc_get_latest_value(ADC);
// 		distance = calc_dist(adc_val);
// 		newerr = setpoint - distance;
// 		offset = 500;
// 		output = offset -(k_prop * newerr);
		regulate_P(adc_val);

		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}

uint16_t calc_dist(uint16_t adcvalue)
{
	int i = adcvalue/10;
	int r_calc = conv_arr[i];
	int f_calc = (conv_arr[i] - r_calc) * (adcvalue % 10);
	return r_calc + f_calc;
}

void update_vars(int16_t new_error, uint16_t new_pwm, uint16_t new_dist)
{
	if(xSemaphoreTake(semph, portMAX_DELAY))
	{
		distance_val = new_dist;
		pwm_val = new_pwm;
		error_val = new_error;
		xSemaphoreGive(semph);
	}
}

void regulate_P(uint16_t adcvalue)
{
	int distance = calc_dist(adcvalue);
	int newerr = setpoint - distance;
	int offset = 500;
	uint16_t outpt = offset -(k_prop * newerr);
	pwm_set_value(outpt);
	update_vars(newerr, outpt, distance);
}

void regulate_PID(uint16_t adcvalue)
{
	int distance = calc_dist(adcvalue);
	int newerr = distance - setpoint;
	int offset = 500;
	
	int d_error = olderr - newerr;
	integ = integ + ((1000/periodicity)/k_int)*newerr;
	uint16_t outpt = k_prop*(-newerr );
	pwm_set_value(outpt);
	update_vars(newerr, outpt, distance);
	olderr = newerr;
}