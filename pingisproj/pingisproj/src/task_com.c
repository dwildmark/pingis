/*
 * task_com.c
 *
 * Created: 2016-03-12 17:48:36
 *  Author: Spellabbet
 */ 

#include <asf.h>

void task_com(void *pvParameters)
{
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = 10;
	
	xLastWakeTime = xTaskGetTickCount();
	
	char buffer[50] = {0};
		
	while(1)
	{
		gets(buffer);
		printf(buffer);
		printf("\n");

	}
}