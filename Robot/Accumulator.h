#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"
#include <stdlib.h>

class Accumulator {
private:
	Victor accumulateVic;

	enum {
		ACCUMULATING, NOT_ACCUMULATING, PASSING
	} state;

public:
	void update();
	void disable();
	Accumulator();
	void runCommand(RobotCommand newCommand);
};

#endif
