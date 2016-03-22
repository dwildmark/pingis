/*
 * task_reg.c
 *
 *
 *  Author: Dennis Wildmark, Olle Casperson
 */ 

#include <asf.h>
#include "common.h"
#include "pwm_func.h"
#include "task_reg.h"

/************************************************************************/
/* Task for controlling the system. Execution periodicity is set from   */
/* Matlab in the start-up.                                              */
/************************************************************************/
void task_reg(void *pvParameters)
{
	
	portTickType xLastWakeTime;
	const portTickType xTimeIncrement = periodicity;
	
	xLastWakeTime = xTaskGetTickCount();
	
	uint16_t adc_val;
	
	pwm_set_value(500);
	delay_ms(3000);
	
	while(1) {
		adc_start(ADC);
		while((adc_get_status(ADC) & 0x1<<24)==0);
		adc_val = adc_get_latest_value(ADC);
		regulate_PID(adc_val);
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}

/************************************************************************/
/* Function that turns an ADC-value to a millimeter value.              */
/* Uses the adc-value as an index in the array that contains linear     */
/* values for the distance sensor.                                      */
/************************************************************************/
uint16_t calc_dist(uint16_t adcvalue)
{
	/* Chooses index from filtered ADC-value */
	int i = filter_adc(adcvalue/10) - 1;
	/* Index is subtracted by one because the array begins on index 0 in C */
	int r_calc = conv_arr[i];
	/* By using the delta between i - 1 and i values and multiplying       */
	/* it by the digit in the ADC-value that we lose in the first step     */
	/* we interpolate and get a more accurate value						   */
	int f_calc = (conv_arr[i + 1] - r_calc) * (float)((adcvalue % 10) / 10);
	return r_calc - f_calc;
}

/************************************************************************/
/* Function that updates the values if the semaphore isn't taken        */
/* by the other task.                                                   */
/************************************************************************/
void update_vars(int16_t new_error, uint16_t new_pwm, uint16_t new_dist)
{
	if(xSemaphoreTake(semph, portMAX_DELAY))
	{
		distance_val = new_dist;
		pwm_val = new_pwm;
		error_val = new_error;
		xSemaphoreGive(semph);
	}
}

/* P-controller, used to determine PID-values */
// void regulate_P(uint16_t adcvalue)
// {
// 	int distance = calc_dist(adcvalue);
// 	int newerr = distance - setpoint;
// 	int offset = 500;
// 	uint16_t outpt = offset (k_prop * newerr);
// 	pwm_set_value(outpt);
// 	update_vars(newerr, outpt, distance);
// }


/* PID-controller. Uses the three PID-values received in the startup */
void regulate_PID(uint16_t adcvalue)
{
	static int sum_err = 0;	//Variable that holds the sum of errors	
	static int old_err = 0; //Variable that holds the error from last function call
	const float dT = (float) periodicity/1000; //Calculate the time step
	int real_dist = calc_dist(adcvalue); //ADC-value converted to millimeters
	int new_err = real_dist - setpoint; //Current error
	sum_err += new_err; //add the new error to the error sum
	sum_err = max(min(sum_err, INTEG_LIM), -INTEG_LIM); //Limit the error sum from INTEG_LIM to (-INTEG_LIM)
	int d_err = old_err - new_err; //difference in error from last function call, used in the derivative part
	
	/* Calculates the proportional, integral and derivative parts of the controller value */
	float prop = (k_prop) * (float)new_err;
	float integ = (k_prop) * (float)((dT * sum_err)/k_int);
	float deriv = (k_prop) * (float)((d_err/dT) * k_deriv);
	
	int pwm_outval = OFFSET + (int)(prop + integ + deriv); //
	pwm_set_value(pwm_outval); //Write control value to pwm
	update_vars(new_err, pwm_outval, real_dist); //Update variables for plot
	old_err = new_err; //Set old error to new error
}

/* FIR-filter that filters an ADC-value to accommodate for interference */
uint16_t filter_adc(uint16_t invalue)
{
	static float xb[4] = {0}; //Buffer to hold the values. Static, so it doesn't reset between function calls.
		
	/* Coefficients that creates a floating average FIR */
	static float b[4] = {0.25, 0.25, 0.25, 0.25};
		
	uint16_t filtered_val = 0;
	
	/* Shift the values one step to the right */
	for(int k = 2;k >= 0;k--)
	{
		xb[k+1] = xb[k];
	}
	/* Puts the new value first */
	xb[0] = invalue;
	
	/* Sums up the filter value */
	for(int k = 0;k <= 3;k++)
	{
		filtered_val += b[k]*xb[k];
	}
	
	return filtered_val;
}
