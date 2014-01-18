#include <WPILib.h>
#include "Constants.h"

class Accumulator{
private:
	Victor vic5;
	Victor vic6;
	Victor vic7;
	
	Encoder enc1;
	Encoder enc2;
	
public:
	void up();
	void down();
	void update();
	Accumulator();
};

