#ifndef RANGEFINDER_H
#define RANGEFINDER_H
#include <WPILib.h>
#include <math.h>
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"


class Rangefinder {
	private:
		//constructors for ultrasonic rangefinders
		// Our Ultrasonic sensors are analog, so we can't use the ultrasonic object provided by WPILib
		AnalogChannel ultraLeft;
		AnalogChannel ultraRight;
		Robot* robot;

	public:
		Rangefinder(Robot* robotPointer);
		double measureAngle(); 
		void rotateToWall();
		float wallDist();
		void setDistToWall(float dist);
		void runCommand(RobotCommand command);
};

#endif
