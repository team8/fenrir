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
	Timer time;
	Robot* robot;
	bool targetReached;
	void path();
	double shootDist;
	double spawnDist;
	bool pathCalled;
	bool hasShot;
};
#endif
