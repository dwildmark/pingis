/*
 * This file contains a task used for communication
 * with a serial interface.
 * 
 *  Author: Dennis Wildmark, Olle Casperson
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
		/* If the semaphore is available, send the values over serial */
		if(xSemaphoreTake(semph, portMAX_DELAY))
		{
			itoa(error_val, str, 10);
			printf(str);
			printf("\n");
			
			itoa(pwm_val, str, 10);
			printf(str);
			printf("\n");
			
			itoa(distance_val, str, 10);
			printf(str);
			printf("\n");
			
			xSemaphoreGive(semph);
		}
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}