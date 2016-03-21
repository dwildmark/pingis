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

void task_reg(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = periodicity;
	
	xLastWakeTime = xTaskGetTickCount();
	
	uint16_t adc_val;
	
	pwm_set_value(500);
	delay_ms(3000);
	
	while(1) {
		adc_start(ADC);
		while((adc_get_status(ADC) & 0x1<<24)==0);
		adc_val = adc_get_latest_value(ADC);
		regulate_PID(adc_val);
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}

uint16_t calc_dist(uint16_t adcvalue)
{
	static float xbuff[4] = {0};
	static float b[4] = {0.25,0.25,0.25,0.25};
	uint16_t temp = 0;
	for(int k = 2;k >= 0;k--)
	{
		xbuff[k+1] = xbuff[k];
	}
	xbuff[0] = adcvalue;
	
	for(int k = 0;k <= 3;k++)
	{
		temp += b[k]*xbuff[k];
	}
	int i = temp/10;
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
	const float dT = (float) periodicity/1000;
	static int sum_err = 0;
	static int old_err = 0;
	int real_dist = calc_dist(adcvalue);
	int new_err = setpoint - real_dist;
	int integ_lim = 150000;
	sum_err += new_err;
	sum_err = max(min(sum_err, integ_lim), -integ_lim);
	int d_err = old_err - new_err;
	float prop = (float) (new_err * (-k_prop));
	float integ = (float) ((dT * sum_err)/k_int) * (-k_prop);
	float deriv = (float) ((d_err/dT) * k_deriv) * (-k_prop);
	float sum = prop + integ + deriv;
	int pwm_val = (int) (500 + sum);
	pwm_set_value(pwm_val);
	update_vars(new_err, pwm_val, real_dist);
	old_err = new_err;
}