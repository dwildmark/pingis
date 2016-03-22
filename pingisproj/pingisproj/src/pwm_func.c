/*
 * This file holds functions for initializing and using the PWM device.
 *
 *  Author: Dennis Wildmark, Olle Casperson
 */ 
#include <asf.h>
#include "pwm_func.h"

static pwm_channel_t pwm_instance;

/************************************************************************/
/* Function initializes the PWM with the defined settings               */
/************************************************************************/
int pwm_config(void)
{
	if(pmc_enable_periph_clk(ID_PWM) == 0) {
		pwm_channel_disable(PWM, PWM_CHANNEL_0);
		pwm_clock_t pwmclock = {
			.ul_clka = PWM_FREQUENCY * PWM_RESOLUTION,
			.ul_clkb = 0,
			.ul_mck = sysclk_get_cpu_hz()
		};
		pwm_init(PWM, &pwmclock);
		pwm_instance.alignment = PWM_ALIGN_LEFT;
		pwm_instance.polarity = PWM_LOW;
		pwm_instance.ul_prescaler = PWM_CMR_CPRE_CLKA;
		pwm_instance.ul_period = PWM_RESOLUTION;
		pwm_instance.ul_duty = 0;
		pwm_instance.channel = PWM_CHANNEL_0;
		pwm_channel_init(PWM, &pwm_instance);
		pio_set_peripheral(PWM_PIO, PWM_PIO_PERIPHERAL, PWM_PIO_PIN);
		pwm_channel_enable(PWM, PWM_CHANNEL_0);
		return 0;
	}
	return 1;
}

/************************************************************************/
/* Function sets PWM dutycycle to the provided value.                   */
/* It also limits it to between 0 and PWM_RESOLUTION.                   */
/************************************************************************/
void pwm_set_value(uint32_t dutycycle)
{
 	dutycycle = min(max(dutycycle, 0), 999);
	pwm_channel_update_duty(PWM, &pwm_instance, dutycycle);
}