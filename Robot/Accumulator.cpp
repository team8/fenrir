#include "Accumulator.h"

Accumulator::Accumulator() :
	accumulateVic((uint32_t) PORT_ACCUMULATOR_VIC_7) {
	std::printf("Accumulator constructor\n");
}

void Accumulator::runCommand(RobotCommand newCommand) {
	switch (newCommand.getMethod().accumulatorMethod) {
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

void Accumulator::disable() {
	accumulateVic.Set(0.0);
}

void Accumulator::update() {
	switch (state) {
		case NOT_ACCUMULATING:
			accumulateVic.Set(0);
		break;
		case ACCUMULATING:
			accumulateVic.Set(-.8);
			//std::printf("case Accumulating \n");
		break;
		case PASSING:
			accumulateVic.Set(.8);
			//std::printf("passing \n");
		break;
	}
}

