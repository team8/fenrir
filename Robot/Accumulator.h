#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum{
	ACCUMULATING,
	NOT_ACCUMULATING,
	PASSING
} AccumulatorState;

class Accumulator{
private:
	Victor accumulateVic;
	AccumulatorState state;
public:
	void accumulate();
	void stop();
	void update();
	Accumulator();
	void runCommand(RobotCommand newCommand);
};

