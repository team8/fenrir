#include "Accumulator.h"

Accumulator::Accumulator():
	accumulateVic((uint32_t)PORT_ACCUMULATOR_VIC_7)
	{

	}

void Accumulator::runCommand(RobotCommand newCommand) {
	switch(newCommand.getMethod().accumulatorMethod) {
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

void Accumulator::notAccumulating() {

}

bool getHeld() {
	return ballHeld;
}

void setHeld(bool b){
	ballHeld = b;
}

void Accumulator::update() {
	switch(state) {
	case NOT_ACCUMULATING:
		accumulateVic.Set(0);
		break;
	case ACCUMULATING:
		accumulateVic.Set(0.5);
		break;
	case PASSING:
		accumulateVic.Set(-0.5);
		break;
	}
}

