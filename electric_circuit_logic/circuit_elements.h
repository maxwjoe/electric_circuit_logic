#ifndef CIRCUIT_ELEMENTS_H
#define CIRCUIT_ELEMENTS_H


float* resistor(float V_IN, float V_DROP);
float* diode(float ANODE, float V_IN, float Forward_V);
void electrical_buffer(float* V_IN, float hi, float vcc);


#endif 

