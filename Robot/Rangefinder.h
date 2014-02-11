#ifndef RANGEFINDER_H
#define RANGEFINDER_H
#include <WPILib.h>
#include <math.h>
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"


class Rangefinder {
	private:
		//constructors for left ultrasonic rangefinders	
		Ultrasonic ultraLeft;
		Ultrasonic ultraRight;
		Robot* robot;

	public:
		Rangefinder(Robot* robotPointer);
		double measureAngle(); 
		void rotateDegrees();
		float wallDist();
		void setDistToWall(float dist);
		void runCommand(RobotCommand command);
};

#endif
