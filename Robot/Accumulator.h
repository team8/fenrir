#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum{
	ACCUMULATING,
	NOT_ACCUMULATING,
	PASSING
} AccumulatorState;

//Methods used for the Command
typedef enum{
	ACCUMULATE,
	STOP,
	PASS
} AccumulatorMethod;

typedef enum{
	FOWARD,
	BACKWARD,
	HALT
}ExtensionMethod;
	
class Accumulator{
private:
	Victor accumulateVic;
	AccumulatorState state;
	
	Encoder encoder;
	PIDController encController;
public:
	void accumulate();
	void stop();
	void update();
	Accumulator();
	void runCommand(RobotCommand newCommand);
};

