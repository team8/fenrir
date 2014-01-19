#include "Accumulator.h"

Accumulator::Accumulator():
	leftVic(PORT_ACCUMULATOR_VIC_5),
	rightVic(PORT_ACCUMULATOR_VIC_6),
	accumulateVic(PORT_ACCUMULATOR_VIC_7),
	
	enc1((uint32_t)PORT_ACCUMULATOR_ENC_1A, (uint32_t)PORT_ACCUMULATOR_ENC_1B),
	enc2((uint32_t)PORT_ACCUMULATOR_ENC_2A, (uint32_t)PORT_ACCUMULATOR_ENC_2B)

{
		
}
void Accumulator::deploy(){
	
}
void Accumulator::retract(){
	
}
void Accumulator::accumulate(){
	
}
void Accumulator::update(){

}
