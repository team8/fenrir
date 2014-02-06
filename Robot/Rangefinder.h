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
		//constructors for left ultrasonic rangefinders	
		Ultrasonic ultraLeft;
		Ultrasonic ultraRight;
		Robot* robot;

	public:
		double measureAngle(); 
		void rotateDegrees();
		float wallDist();
		Rangefinder(Robot* robotPointer);
};

#endif
