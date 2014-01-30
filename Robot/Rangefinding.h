#ifndef RANGEFINDING_H
#define RANGEFINDING_H
#include <stdlib.h>
#include "RobotCommand.h"
#include "Drivetrain.h"
#include "Robot.h"
#include "Constants.h"
#include <WPILib.h>
#include <math.h>

class Robot;

class Rangefinding {
	private:
		Ultrasonic ultraLeft;
		Ultrasonic ultraRight;
		Robot * robot;

	public:
		void rotateDegrees(); // Returns the amount of degrees of rotation needed to be perpendicular to the wall
		double getDistance();
		Rangefinding(Robot * robotPointer);
};
#endif
