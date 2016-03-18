/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
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

xSemaphoreHandle semph = 1;

float k_prop;
float k_int;
float k_deriv;
uint16_t setpoint;
uint16_t periodicity;
char str[100] = {0};
uint16_t conv_arr[100] = {0};
uint16_t testval = 0;

uint16_t error_val = 0;
uint16_t pwm_val = 0;
uint16_t ctrl_val = 0;

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	ioport_init();
	configure_console();
	motorshield_init();
	adc_config();
	pwm_config();
	param_init();
	vSemaphoreCreateBinary(semph);

	//Testing purposesssss
	
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
	
	//end of testttttt
	
	xTaskCreate(task_com, (const signed char * const) "Com", TASK_COM_STACKSIZE, NULL, 2, NULL);
	xTaskCreate(task_reg, (const signed char * const) "Reg", TASK_COM_STACKSIZE, NULL, 2, NULL);
	vTaskStartScheduler();

	/* Insert application code here, after the board has been initialized. */
}
