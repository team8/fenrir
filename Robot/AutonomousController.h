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
		void startTimer();
	private:
		Timer time;
		Robot* robot;
		void drive(float v = 0.7);
		void stop();
		bool shoot();
		bool targetReached;
		void pathOne();
		void pathTwo();
		void pathThree();
};
#endif
