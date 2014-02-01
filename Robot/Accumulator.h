#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"
#include <stdlib.h>


	
class Accumulator{
private:
	Victor accumulateVic;
	Victor accumulateVic2;
	Victor accumulateVic3;
	Victor accumulateVic4;
	Victor accumulateVic5;
	Victor accumulateVic6;
	Victor accumulateVic7;

	
	typedef enum{
		ACCUMULATING,
		NOT_ACCUMULATING,
		PASSING
	} AccumulatorState;
	AccumulatorState state;

public:
	void accumulate();
	void notAccumulating();
	void update();
	
	Accumulator();
	void runCommand(RobotCommand newCommand);
};

#endif
