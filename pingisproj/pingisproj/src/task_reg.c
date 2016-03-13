/*
 * task_reg.c
 *
 * Created: 2016-03-12 17:55:13
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "common.h"

void task_reg(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = howoftenval;
	
	xLastWakeTime = xTaskGetTickCount();
	
	while(1) {
		
	}
}