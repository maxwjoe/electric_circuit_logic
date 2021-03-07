#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

float* electrical_AND(float V1, float V2, float V_IN, float v_drop, float fwd_v);
float electrical_NAND(float V1, float V2, float V_IN);
float* electrical_OR(float V1, float V2, float fwd_v);
float electrical_four_AND(float V1, float V2, float V3, float V4, float VCC);


#endif