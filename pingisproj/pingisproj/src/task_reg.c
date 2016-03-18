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
	
	while(1) {
		
		adc_start(ADC);
		while((adc_get_status(ADC) & 0x1<<24)==0);
		uint16_t adc_val = adc_get_latest_value(ADC);
		uint16_t distance = conv_arr[adc_val/10];
		int16_t newerr = setpoint - distance;
		uint16_t offset = 500;
		uint16_t output = offset - k_prop * newerr;

		pwm_val = distance;
		pwm_set_value(output);
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}