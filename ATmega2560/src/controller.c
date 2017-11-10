/*
 * controller.c
 *
 * Created: 10.11.2017 10:47:36
 *  Author: ingunnjv
 */ 
#include "controller.h"
#include "setup.h"

float Kp = 1;
float Ki = 0.5;

volatile uint16_t *timer = &TCNT1;

uint8_t CONTROLLER_set_reference(uint8_t reference)
{
	//printf("\nReference: (%d)\n", reference);
	reference = abs(reference - 255); // 255 is rightmost position, 0 is leftmost position
	printf("\n\nReference: (%d) \n", reference);
	return reference;
	
}

uint8_t CONTROLLER_run(uint8_t y, uint8_t reference)
{
	static float integral;
	uint8_t error;
	uint8_t u;
	float dt = (float)*timer/F_CPU;
	*timer = 0;
	
	if (y < 0){ y = 0; }
	error = reference - y;
	integral = integral + error*dt;
	u = Kp*error; + Ki*integral;
	return u;
}
