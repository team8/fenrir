#include "Accumulator.h"

Accumulator::Accumulator():
	//accumulateVic((uint32_t)PORT_ACCUMULATOR_VIC_7)
	accumulateVic((uint32_t) 1),
	accumulateVic2((uint32_t) 2),
	accumulateVic3((uint32_t) 3),
	accumulateVic4((uint32_t) 4),
	accumulateVic5((uint32_t) 5),
	accumulateVic6((uint32_t) 6),
	accumulateVic7((uint32_t) 7)


	
{

}

void Accumulator::runCommand(RobotCommand newCommand){
	
	switch(newCommand.getMethod().accumulatorMethod){
	case RobotCommand::STOP:
		state = NOT_ACCUMULATING;
		break;
	case RobotCommand::ACCUMULATE:
		state = ACCUMULATING;
		break;
	case RobotCommand::PASS:
		state = PASSING;
		break;
	}
}

void Accumulator::notAccumulating(){

}

void Accumulator::update(){
	switch(state){
	case NOT_ACCUMULATING:
		accumulateVic.Set(0);
		break;
	case ACCUMULATING:
		accumulateVic.Set(0.5);
		accumulateVic2.Set(0.5);
		accumulateVic3.Set(0.5);
		accumulateVic4.Set(0.5);
		accumulateVic5.Set(0.5);
		accumulateVic6.Set(0.5);
		accumulateVic7.Set(0.5);

		break;
	case PASSING:
		accumulateVic.Set(-0.5);
		break;
	}
}

