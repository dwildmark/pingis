/*
 * task_reg.c
 *
 * Created: 2016-03-12 17:55:13
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "common.h"
#include "pwm_func.h"

void task_reg(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = howoftenval;
	
	xLastWakeTime = xTaskGetTickCount();
	
	while(1) {
// 		adc_start(ADC);
// 		while((adc_get_status(ADC) & 0x1<<24)==0);
// 		testval = adc_get_latest_value(ADC);
		pwm_set_value(testval);
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}