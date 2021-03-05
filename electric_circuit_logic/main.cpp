#include <stdio.h>
#include <stdlib.h>

#define DIODE_FORWARD_VOLTAGE 0.7f
#define RESISTOR_VALUE 
#define POWER_SUPPLY 5.0f
#define HI_MIN 2.0f
#define LOW_MAX 0.8f

//Prototypes
	//Electrical Components
float resistor(float V_IN, float V_DROP); //High Level Implementation with preset Voltage Drop
void diode(float ANODE, float* V_IN, float Forward_V);
	//Logic Circuits
float electrical_AND(float V1, float V2, float V_IN);
float electrical_NAND(float V1, float V2, float V_IN);
float electrical_OR(float V1, float V2, float VCC);
float electrical_four_AND(float V1, float V2, float V3, float V4, float VCC);
float electrical_buffer(float V_IN);





int main() {

	float circuit_voltage = POWER_SUPPLY;

	diode(4.6f, &circuit_voltage, DIODE_FORWARD_VOLTAGE);
	printf("%f Volts", circuit_voltage);

	return 0;
}

//Takes in 2 Input Voltages and Power -> Returns A voltage based on Inputs
void diode(float ANODE, float* V_IN, float Forward_V){
	if (*V_IN - ANODE > Forward_V) {
		*(V_IN) *= 0.0f; //Current Flows Through Diode -> Voltage Goes to Zero
	}
}