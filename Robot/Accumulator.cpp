#include "Accumulator.h"

Accumulator::Accumulator():
	accumulateVic(PORT_ACCUMULATOR_VIC_7),
	//encoder((uint32_t) port, (uint32_t) port),
	encController(0.1, 0.1, 0.1, &encoder, &accumulateVic)
{
	encoder.Start();
	encController.SetOutputRange(-1, 1);
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
void Accumulator::update(){
	switch(state){
	case NOT_ACCUMULATING:
		notAccumulating();
		accumulateVic.Set(encController.Get());
		break;
	case ACCUMULATING:
		accumulateVic.Set(0.5);
		break;
	case PASSING:
		accumulateVic.Set(-0.5);
		break;
	}
}

void notAccumulating(){
	encoder.Reset();
	encController.SetSetPoint(0);
	encController.Enable();
}

