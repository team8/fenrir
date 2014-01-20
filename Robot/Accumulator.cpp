#include "Accumulator.h"

Accumulator::Accumulator():
	leftVic(PORT_ACCUMULATOR_VIC_5),
	rightVic(PORT_ACCUMULATOR_VIC_6),
	accumulateVic(PORT_ACCUMULATOR_VIC_7),
	
	enc1((uint32_t)PORT_ACCUMULATOR_ENC_1A, (uint32_t)PORT_ACCUMULATOR_ENC_1B),
	enc2((uint32_t)PORT_ACCUMULATOR_ENC_2A, (uint32_t)PORT_ACCUMULATOR_ENC_2B)

{
		
}
void Accumulator::accumulate(){
	state=ACCUMULATING;
}
void Accumulator::stop(){
	state=IDLE;
}

void Accumulator::runMethod(RobotCommand newCommand){
	switch(newCommand.getMethod().accumulatorMethod){
	case STOP:
		stop()
		break;
	case ACCUMULATE:
		accumulate();
		break;
	}
}
void Accumulator::update(){
	switch(state){
	case IDLE:
		accumulateVic.Set(0);
		break;
	case ACCUMULATING:
		accumulateVic.Set(1.0);
		break;
	}
}
