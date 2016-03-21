/**
 * This application is developed for the ping-pong ball control system. 
 * The application communicates with a Matlab client connected through serial (UART).
 * It runs the small real-time OS FreeRTOS with 2 tasks, one for communication and one for PID-control.
 * 
 *	Author: Dennis Wildmark, Olle Casperson
 */

#include <asf.h>
#include <stdlib.h>
#include "uart_util.h"
#include "task_com.h"
#include "common.h"
#include "task_reg.h"
#include "pwm_func.h"
#include "motorshield.h"
#include "adc_func.h"

uint16_t values[100];

xSemaphoreHandle semph = (xSemaphoreHandle) 1;

float k_prop;
float k_int;
float k_deriv;
uint16_t setpoint;
uint16_t periodicity;
char str[100] = {0};
uint16_t conv_arr[100] = {0};
uint16_t testval = 0;

uint16_t distance_val = 0;
uint16_t pwm_val = 0;
int16_t error_val = 0;

int main (void)
{
	/* Initialize all components of the project */
	sysclk_init();
	board_init();
	ioport_init();
	configure_console();
	motorshield_init();
	adc_config();
	pwm_config();
	param_init(); //Recieve the values that matlab sends and save them
	/* Semaphore is for synchronization of the values between the two tasks */
	vSemaphoreCreateBinary(semph);

	/* Prints out all the variables for confirmation */
	itoa(k_prop * 1000, str, 10);
	printf(str);
	printf("\n");
	itoa(k_int * 1000, str, 10);
	printf(str);
	printf("\n");
	itoa(k_deriv * 1000, str, 10);
	printf(str);
	printf("\n");
	itoa(setpoint * 1000, str, 10);
	printf(str);
	printf("\n");
	itoa(periodicity * 1000, str, 10);
	printf(str);
	printf("\n");
	
	/* Create the two tasks and start the scheduler */
	xTaskCreate(task_com, (const signed char * const) "Com", TASK_COM_STACKSIZE, NULL, 1, NULL);
	xTaskCreate(task_reg, (const signed char * const) "Reg", TASK_COM_STACKSIZE, NULL, 2, NULL);
	vTaskStartScheduler();
}
