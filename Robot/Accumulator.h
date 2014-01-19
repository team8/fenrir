#include <WPILib.h>
#include "Constants.h"

class Accumulator{
private:
	Victor rightVic;
	Victor leftVic;
	Victor accumulateVic;
	
	Encoder enc1;
	Encoder enc2;

	
public:
	void deploy();
	void retract();
	void accumulate();
	void update();
	Accumulator();
};

