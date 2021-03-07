#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "logic_elements.h"

#define DIODE_FORWARD_VOLTAGE 1.0f
#define VOLTAGE_DROP 0.95f //Drop 5%
#define POWER_SUPPLY 5.0f
#define HI_MIN 2.0f
#define LOW_MAX 0.8f

//Prototypes
	//Logic Circuits

//Logical Expression 
float ABorC(float va, float vb, float vc);

int main() {

	printf("\t*** \t   TRUTH TABLE ( F = AB + C ) \t\    ***\n");
	printf("\t||    A     |     B    |     C    |     F    ||\n");

	for (uint8_t i = 0b00000000; i < 0b00001000; i++) {

		//Get Logic Inputs
		float logicC = (float)(0b00000001 & i);
		float logicB = (float)((0b00000010 & i) >> 1);
		float logicA = (float)((0b00000100 & i) >> 2);

		//Convert to Voltage
		float va = logicA * POWER_SUPPLY;
		float vb = logicB * POWER_SUPPLY;
		float vc = logicC * POWER_SUPPLY;

		//Run Logic Circuit
		float vf = ABorC(va, vb, vc);
		
		//Convert Output to Logic 1 or 0 (Or Undefined)
		float logicF = 0;
		if (vf >= HI_MIN) {
			logicF = 1;
		}
		else if (vf <= LOW_MAX) {
			logicF = 0;
		}
		else {
			logicF = -2;
		}

		printf("\t|| %f | %f | %f | %f ||\n", logicA, logicB, logicC, logicF);
	}

	printf("\t-----------------------------------------------\n");

	return 0;
}

// F = AB + C
float ABorC(float va, float vb, float vc) {
	float AND_OUTPUT = *electrical_AND(va, vb, POWER_SUPPLY, VOLTAGE_DROP, DIODE_FORWARD_VOLTAGE);
	float OR_OUTPUT = *electrical_OR(AND_OUTPUT, vc, DIODE_FORWARD_VOLTAGE);
	return OR_OUTPUT;
}




//High Level of Abstraction for an Electrical Buffer
void electrical_buffer(float* V_IN) {
	if (*V_IN >= HI_MIN)
		*V_IN = POWER_SUPPLY;
}