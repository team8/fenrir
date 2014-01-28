#ifndef AUTONOMOUSCONTROLLER_H
#define	AUTONOMOUSCONTROLLER_H
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"
#include <WPILib.h>

class AutonomousController {

	public:
		AutonomousController(Robot* robotPointer);
		void update();
		void startTimer();
	private:
		Timer time; 
		Robot* robot;
		void drive();
		void stop();
		bool shoot();
		bool targetReached;
};
#endif
