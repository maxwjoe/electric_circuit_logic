#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define DIODE_FORWARD_VOLTAGE 1.0f
#define VOLTAGE_DROP 0.95f //Drop 5%
#define POWER_SUPPLY 5.0f
#define HI_MIN 2.0f
#define LOW_MAX 0.8f

//Prototypes
	//Electrical Components
float resistor(float V_IN, float V_DROP); //High Level Implementation with preset Voltage Drop
float diode(float ANODE, float V_IN, float Forward_V);
	//Logic Circuits
float electrical_AND(float V1, float V2, float V_IN);
float electrical_NAND(float V1, float V2, float V_IN);
float electrical_OR(float V1, float V2);
float electrical_four_AND(float V1, float V2, float V3, float V4, float VCC);
void electrical_buffer(float* V_IN);

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
			logicF = NULL;
		}

		printf("\t|| %f | %f | %f | %f ||\n", logicA, logicB, logicC, logicF);
	}

	printf("\t-----------------------------------------------\n");

	return 0;
}

// F = AB + C
float ABorC(float va, float vb, float vc) {
	float AND_OUTPUT = electrical_AND(va, vb, POWER_SUPPLY);
	float OR_OUTPUT = electrical_OR(AND_OUTPUT, vc);
	return OR_OUTPUT;
}

float diode(float ANODE, float CATHODE, float Forward_V){
	if (CATHODE - ANODE > Forward_V) {
		return CATHODE - Forward_V;
	}
	return 0.0f;
}

float resistor(float V_IN, float V_DROP) {
	return V_IN * V_DROP;
}


float electrical_AND(float v1, float v2, float V_IN) {
	float circuit_voltage = resistor(V_IN, VOLTAGE_DROP);
	circuit_voltage -= diode(v1, circuit_voltage, DIODE_FORWARD_VOLTAGE);
	circuit_voltage -= diode(v2, circuit_voltage, DIODE_FORWARD_VOLTAGE);
	return circuit_voltage;
}

float electrical_OR(float v1, float v2) {
	float circuit_voltage = 0.0f;
	circuit_voltage += diode(circuit_voltage, v1, DIODE_FORWARD_VOLTAGE);
	circuit_voltage += diode(circuit_voltage, v2, DIODE_FORWARD_VOLTAGE);
	return circuit_voltage;
}

//High Level of Abstraction for an Electrical Buffer
void electrical_buffer(float* V_IN) {
	if (*V_IN >= HI_MIN)
		*V_IN = POWER_SUPPLY;
}