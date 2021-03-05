#include <stdio.h>
#include <stdlib.h>

#define DIODE_FORWARD_VOLTAGE 3.0f
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
float electrical_OR(float V1, float V2, float VCC);
float electrical_four_AND(float V1, float V2, float V3, float V4, float VCC);
void electrical_buffer(float* V_IN);


int main() {

	float INPUT_A = 5.0f;
	float INPUT_B = 5.0f;
	float OUTPUT_Z = 0.0f;

	OUTPUT_Z = electrical_AND(INPUT_A, INPUT_B, POWER_SUPPLY);
	printf("( V1 = %f , V2 = %f ) -> AND_GATE -> ( VOUT = %f )\n", INPUT_A, INPUT_B, OUTPUT_Z);
	float temp = OUTPUT_Z;
	electrical_buffer(&OUTPUT_Z);
	printf("( VOUT = %f ) -> BUFFER -> ( VOUT = %f )\n", temp, OUTPUT_Z);

}

//Takes in ANODE (Input), CATHODE (V_IN) -> Returns A voltage based on Inputs
float diode(float ANODE, float V_IN, float Forward_V){
	if (V_IN - ANODE > Forward_V) {
		return 0.0f; //Current Flows Through Diode -> Voltage Goes to Zero
	}
	return V_IN;
}

// Emulates a Voltage Drop
float resistor(float V_IN, float V_DROP) {
	return V_IN * V_DROP;
}


float electrical_AND(float V1, float V2, float V_IN) {
	float circuit_voltage = resistor(V_IN, VOLTAGE_DROP);
	circuit_voltage = diode(V1, circuit_voltage, DIODE_FORWARD_VOLTAGE);
	circuit_voltage = diode(V2, circuit_voltage, DIODE_FORWARD_VOLTAGE);
	return circuit_voltage;
}

//High Level of Abstraction for an Electrical Buffer
void electrical_buffer(float* V_IN) {
	if (*V_IN >= HI_MIN)
		*V_IN = POWER_SUPPLY;
}