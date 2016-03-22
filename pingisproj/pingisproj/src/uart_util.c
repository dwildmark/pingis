/*
 * This file contains functions for initializing 
 * UART communication and parameters.
 *
 *  Author: Dennis Wildmark, Olle Casperson
 */ 

#include <asf.h>
#include "uart_util.h"
#include "common.h"

void param_init(void)
{
	char buffer[50] = {0};
	
	gets(buffer);
	k_prop = (float)atoi(buffer)/1000;
	
	gets(buffer);
	k_int = (float)atoi(buffer)/1000;
	
	gets(buffer);
	k_deriv = (float)atoi(buffer)/1000;
	
	gets(buffer);
	setpoint = (int)atoi(buffer);
	
	gets(buffer);
	periodicity = (int)atoi(buffer);
	
	for (int i=0; i<100;i++)
	{
		gets(buffer);
		conv_arr[i] = (float)atof(buffer);
	}
}

void configure_console(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}