#include "Accumulator.h"

Accumulator::Accumulator():
	leftVic(PORT_ACCUMULATOR_VIC_5),
	rightVic(PORT_ACCUMULATOR_VIC_6),
	accumulateVic(PORT_ACCUMULATOR_VIC_7),
	
	enc1((uint32_t)PORT_ACCUMULATOR_ENC_1A, (uint32_t)PORT_ACCUMULATOR_ENC_1B),
	enc2((uint32_t)PORT_ACCUMULATOR_ENC_2A, (uint32_t)PORT_ACCUMULATOR_ENC_2B)
{	
}

void Accumulator::runCommand(RobotCommand newCommand){
	switch(newCommand.getMethod().accumulatorMethod){
	case STOP:
		state = NOT_ACCUMULATING;
		break;
	case ACCUMULATE:
		state = ACCUMULATING;
		break;
	}
	switch(newCommand.getMethod().extensionMethod){
	case FOWARD:
		extensionState = EXTEND;
		break;
	case BACKWARD:
		extensionState = RETRACT;
		break;
	case HALT:
		extensionState = ACCUMULATORSTOP;
		break;
	}
}

void Accumulator::update(){
	switch(state){
	case NOT_ACCUMULATING:
		accumulateVic.Set(0);
		break;
	case ACCUMULATING:
		accumulateVic.Set(1.0);
		break;
	}
	switch(extensionState){
	case EXTEND:
		rightVic.Set(1.0);
		leftVic.Set(-1.0);
		break;
	case RETRACT:
		rightVic.Set(-1.0);
		leftVic.Set(1.0);
		break;
	case ACCUMULATORSTOP:
		rightVic.Set(0.0);
		leftVic.Set(0.0);
		break;
	}
}
