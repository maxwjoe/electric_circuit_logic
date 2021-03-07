#include "circuit_elements.h"

float* diode(float ANODE, float CATHODE, float Forward_V) {
	
	float* return_voltage = (float*)malloc(sizeof(float));

	if (CATHODE - ANODE > Forward_V) {
		*(return_voltage) = CATHODE - Forward_V;
	}
	else {
		*(return_voltage) = 0.0f;
	}
	return return_voltage;
}

float* resistor(float V_IN, float V_DROP) {
	float* return_drop = (float*)malloc(sizeof(float));
		*(return_drop) = V_IN * V_DROP;
		return return_drop;
}


void electrical_buffer(float* V_IN, float hi, float vcc) {
	if (*V_IN >= hi)
		*V_IN = vcc;
}