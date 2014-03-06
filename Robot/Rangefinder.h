#ifndef RANGEFINDER_H
#define RANGEFINDER_H
#include <WPILib.h>
#include <math.h>
#include <stdlib.h>
#include "Constants.h"
#include "RobotCommand.h"


class Rangefinder {
	private:
		//constructors for ultrasonic rangefinders
		AnalogChannel ultraLeft;
		DigitalOutput rxLeft;
		AnalogChannel ultraRight;
		DigitalOutput rxRight;
		
		typedef enum PingState {
			IDLE,
			LEFT,
			PRUNE_LEFT,
			RIGHT,
			PRUNE_RIGHT,
			FINISHED
		} pingState;
		
		PingState state;
		
		double distInch;
		double leftAvg;
		double rightAvg;
		int leftTotal;
		int rightTotal;

	public:
		Rangefinder();
		double measureAngle(); 
		void rotateToWall();
		float wallDist();
		double getDist();
		void setDistToWall(float dist);
		void runCommand(RobotCommand command);
		void update();
};

#endif
