#ifndef ROBOT_H
#define ROBOT_H
#include "Rangefinder.h"
#include <WPILib.h>
#include "Constants.h"
#include "DriveTrain.h"
#include "Shooter.h"
#include "RobotCommand.h"
#include "Accumulator.h"


class Robot {
	private:
		DriveTrain driveTrain;
		Shooter shooter;
		Accumulator accumulator;
		Rangefinder rangefinder;

	public:
		Robot();
		//void setSpeed(float s);
		//void rotateSpeed(float s);
		void setCommand(RobotCommand newCommand);
		void update();
		void disable();
		void runCommand(RobotCommand command);
		void init();
		double getRightEnc();
		double getLeftEnc();
};
#endif
