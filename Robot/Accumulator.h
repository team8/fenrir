#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum{
	ACCUMULATING,
	NOT_ACCUMULATING
} AccumulatorState;
typedef enum{
	EXTEND,
	RETRACT,
	ACCUMULATORSTOP
}AccumulatorExtension;

class Accumulator{
private:
	Victor rightVic;
	Victor leftVic;
	Victor accumulateVic;
	
	Encoder enc1;
	Encoder enc2;
	AccumulatorState state;
	AccumulatorExtension extensionState;

	
public:
	void accumulate();
	void stop();
	void update();
	Accumulator();
	void runCommand(RobotCommand newCommand);
};

