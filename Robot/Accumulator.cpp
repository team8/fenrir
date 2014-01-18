#include "Accumulator.h"

Accumulator::Accumulator():
	vic5(PORT_ACCUMULATOR_VIC_5),
	vic6(PORT_ACCUMULATOR_VIC_6),
	vic7(PORT_ACCUMULATOR_VIC_7),
	
	enc1((uint32_t)PORT_ACCUMULATOR_ENC_1A, (uint32_t)PORT_ACCUMULATOR_ENC_1B),
	enc2((uint32_t)PORT_ACCUMULATOR_ENC_2A, (uint32_t)PORT_ACCUMULATOR_ENC_2B)

{
		
}
void Accumulator::up(){
	
}
void Accumulator::down(){
	
}
