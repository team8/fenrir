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
private:
	Robot* robot;
	double shootDist;
	double spawnDist;
	void path();
	bool pathCalled;
};
#endif
