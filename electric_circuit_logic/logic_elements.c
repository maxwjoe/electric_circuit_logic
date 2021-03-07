#include "logic_elements.h"
#include "circuit_elements.h"



float* electrical_AND(float v1, float v2, float V_IN, float v_drop, float fwd_v) {

	float* circuit_voltage = (float*)malloc(sizeof(float));
	*(circuit_voltage) = *resistor(V_IN, v_drop);
	*(circuit_voltage) -= *diode(v1, *circuit_voltage, fwd_v);
	*(circuit_voltage) -= *diode(v2, *circuit_voltage, fwd_v);
	return circuit_voltage;
}

float* electrical_OR(float v1, float v2, float fwd_v) {
	float* circuit_voltage = (float*)malloc(sizeof(float));
	*circuit_voltage = 0.0f;
	*(circuit_voltage) += *diode(*circuit_voltage, v1, fwd_v);
	*(circuit_voltage) += *diode(*circuit_voltage, v2, fwd_v);
	return circuit_voltage;
}