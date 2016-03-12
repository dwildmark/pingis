/*
 * uart_util.c
 *
 * Created: 2016-03-12 17:41:31
 *  Author: Spellabbet
 */ 

#include <asf.h>
#include "common.h"

void param_init(void)
{
	char buffer[50] = {0};
	
	gets(buffer);
	k_prop = (float)atoi(buffer);
	
	gets(buffer);
	k_int = (float)atoi(buffer);
	
	gets(buffer);
	k_deriv = (float)atoi(buffer);
	
	gets(buffer);
	shouldbeval = (int)atoi(buffer);
	
	gets(buffer);
	howoftenval = (int)atoi(buffer);
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