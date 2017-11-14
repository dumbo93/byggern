/*
 * controller.c
 *
 * Created: 10.11.2017 10:47:36
 *  Author: ingunnjv
 */ 
#include "controller.h"
#include "setup.h"
#include <math.h>

float Kp = 0.7;
float Ki = 0.8;

volatile uint16_t *timer = &TCNT1;

float CONTROLLER_set_reference(uint8_t reference)
{
	float reff;
	//printf("\nReference: (%d)\n", reference);
	reff = abs(reference - 255); // 255 is rightmost position, 0 is leftmost position
	printf("\n\nReference: (%d) \n", (int)reff);
	return reff;
	
}

uint8_t CONTROLLER_run(float y, float reference)
{
	static float integral;
	float error;
	float u;
	float dt = (float)*timer/F_CPU;
	*timer = 0;
	
	
	error = reference - y;
	integral = integral + error*dt;
	u = Kp*error + Ki*integral;
	//printf("\nInput u: %d\n", (int)u);
	//printf("Output y: %d\n", (int)y);
	//printf("Reference: %d\n", (int)reference);
	//printf("Error: %d\n", (int)error);
	//printf("Integral: %d\n\n", (int)integral);
	
	return (uint8_t)u;
}
