#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"
#include <stdlib.h>

class Accumulator {
private:
	Victor accumulateVic;
	typedef enum {
		ACCUMULATING, NOT_ACCUMULATING, PASSING
	} AccumulatorState;
	AccumulatorState state;
	bool ballHeld;

public:
	void accumulate();
	void notAccumulating();
	void update();
	void disable();
	bool getHeld();
	void setHeld();
	Accumulator();
	void runCommand(RobotCommand newCommand);
};

#endif
