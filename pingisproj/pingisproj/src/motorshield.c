/*
 * motorshield.c
 *
 * Created: 2016-02-19 13:59:23
 *  Author: Dennis Wildmark, Olle Casperson
 */ 

#include <asf.h>
#include "motorshield.h"

/* Function initializes pins for the motorshield and sets them to the correct initial value */
void motorshield_init(void)
{
	ioport_set_pin_dir(PWM_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PWM_PIN, IOPORT_PIN_LEVEL_LOW);
	ioport_set_pin_dir(DIRECTION_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(DIRECTION_PIN, IOPORT_PIN_LEVEL_HIGH);
}