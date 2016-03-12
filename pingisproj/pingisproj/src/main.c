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
#include "uart_util.h"
#include "task_com.h"
#include "common.h"

uint16_t values[100];

float k_prop;
float k_int;
float k_deriv;
uint16_t shouldbeval;
uint16_t howoftenval;
char str[100] = {0};

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	ioport_init();
	configure_console();
	param_init();
	
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
	itoa(shouldbeval * 1000, str, 10);
	printf(str);
	printf("\n");
	itoa(howoftenval * 1000, str, 10);
	printf(str);
	printf("\n");
	
	//end of testttttt
	
	
	xTaskCreate(task_com, (const signed char * const) "Com", TASK_COM_STACKSIZE, NULL, 2, NULL);
	vTaskStartScheduler();

	/* Insert application code here, after the board has been initialized. */
}
