#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum{
	ACCUMULATING,
	NOT_ACCUMULATING,
	PASSING
} AccumulatorState;
//Methods used for the Accumulator
typedef enum /*AccumulatorMethod*/{
	ACCUMULATE,
	STOP,
	PASS
} AccumulatorMethod;

//	typedef enum AccumulatorExtensionMethod{
//		FOWARD,
//		BACKWARD,
//		HALT
//	};
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

