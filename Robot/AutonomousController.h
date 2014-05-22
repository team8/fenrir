#ifndef AUTONOMOUSCONTROLLER_H
#define	AUTONOMOUSCONTROLLER_H
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"
#include <WPILib.h>
#include <math.h>

class AutonomousController {
public:
	AutonomousController(Robot* robotPointer);
	void update();
	void init();
private:
	Robot* robot;
	double shootDist;
	double spawnDist;
<<<<<<< HEAD
	void path();
	bool pathCalled;
=======
>>>>>>> 31bd69e6a30d3a919f84c6abdf2bcd4abd38475f
};
#endif
