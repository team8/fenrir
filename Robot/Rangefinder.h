#ifndef RANGEFINDER_H
#define RANGEFINDER_H
#include <WPILib.h>
#include <math.h>
#include "Robot.h"
#include "Constants.h"
#include "RobotCommand.h"
#include "Drivetrain.h"

class Rangefinder {
	private:
		Ultrasonic ultraLeft;
		Ultrasonic ultraRight;
		Robot* robot;

	public:
		void rotateDegrees();
		int wallDist();
		Rangefinder(Robot* robotPointer);
};

#endif
