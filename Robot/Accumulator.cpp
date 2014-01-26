#include "Accumulator.h"

Accumulator::Accumulator():
	accumulateVic(PORT_ACCUMULATOR_VIC_7)
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
	case PASS:
		state = PASSING;
		break;
	}
}
void Accumulator::update(){
	switch(state){
	case NOT_ACCUMULATING:
		accumulateVic.Set(0.0);
		break;
	case ACCUMULATING:
		accumulateVic.Set(0.5);
		break;
	case PASSING:
		accumulateVic.Set(-0.5);
		break;
	}
}

