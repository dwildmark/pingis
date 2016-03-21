/*
 * task_reg.c
 *
 * Created: 2016-03-12 17:55:13
 *  Author: Dennis Wildmark, Olle Casperson
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
	int i = filter_adc(adcvalue)/10;
	int r_calc = conv_arr[i-1];
	int f_calc = (conv_arr[i] - r_calc) * (float)((adcvalue % 10) / 10);
	return r_calc - f_calc;
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
/* P-controller, used to determine PID-values */
// void regulate_P(uint16_t adcvalue)
// {
// 	int distance = calc_dist(adcvalue);
// 	int newerr = setpoint - distance;
// 	int offset = 500;
// 	uint16_t outpt = offset -(k_prop * newerr);
// 	pwm_set_value(outpt);
// 	update_vars(newerr, outpt, distance);
// }


/* PID-controller. Uses the three PID-values received in the startup */
void regulate_PID(uint16_t adcvalue)
{
	static int sum_err = 0;	//Variable that holds the sum of errors	
	static int old_err = 0; //Variable that holds the error from last function call
	const float dT = (float) periodicity/1000; //Calculate the time step
	int real_dist = calc_dist(adcvalue); //ADC-value converted to millimeters
	int new_err = setpoint - real_dist; //Current error
	int integ_lim = 150000; //A limit for the integral part, reduces 
	sum_err += new_err; //
	sum_err = max(min(sum_err, integ_lim), -integ_lim);
	int d_err = old_err - new_err;
	float prop = (-k_prop) * (float)new_err;
	float integ = (-k_prop) * (float)((dT * sum_err)/k_int);
	float deriv = (-k_prop) * (float)((d_err/dT) * k_deriv);
	int pwm_outval = (int) (OFFSET + + prop + integ + deriv);
	pwm_set_value(pwm_outval);
	update_vars(new_err, pwm_outval, real_dist);
	old_err = new_err;
}

uint16_t filter_adc(uint16_t invalue)
{
	static float xbuff[4] = {0};
	static float b[4] = {0.1590552379689, 0.3121634809933, 0.3121634809933, 0.1590552379689};
	uint16_t temp = 0;
	for(int k = 2;k >= 0;k--)
	{
		xbuff[k+1] = xbuff[k];
	}
	xbuff[0] = invalue;
	
	for(int k = 0;k <= 3;k++)
	{
		temp += b[k]*xbuff[k];
	}
	return temp;
}