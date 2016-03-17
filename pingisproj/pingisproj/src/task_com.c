/*
 * task_com.c
 *
 * Created: 2016-03-12 17:48:36
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "common.h"

void task_com(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 50;
	char str[100] = {0};
	xLastWakeTime = xTaskGetTickCount();
		
	while(1)
	{
		if(xSemaphoreTake(semph, portMAX_DELAY))
		{
			itoa(error_val, str, 10);
			printf(str);
			printf("\n");
			itoa(pwm_val, str, 10);
			printf(str);
			printf("\n");
			itoa(ctrl_val, str, 10);
			printf(str);
			printf("\n");
			xSemaphoreGive(semph);
		}
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}