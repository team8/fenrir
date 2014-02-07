#include "Rangefinder.h"

Rangefinder::Rangefinder(Robot* robotPointer) :
	ultraLeft((uint32_t)ULTRASONIC_ECHO_PULSE_OUTPUT_1, (uint32_t)ULTRASONIC_TRIGGER_PULSE_INPUT_1),
	ultraRight((uint32_t)ULTRASONIC_ECHO_PULSE_OUTPUT_2, (uint32_t)ULTRASONIC_TRIGGER_PULSE_INPUT_2)
{
	this -> robot = robotPointer;
	
	ultraLeft.SetAutomaticMode(false);
	ultraRight.SetAutomaticMode(false);
}

void Rangefinder::rotateDegrees() {
	ultraLeft.Ping();
	if (ultraLeft.IsRangeValid()) {
		double leftDist = ultraLeft.GetRangeInches();
		ultraRight.Ping();
		if (ultraRight.IsRangeValid()) {
			double rightDist = ultraRight.GetRangeInches();
			double angle = atan((leftDist - rightDist) / ULTRA_GAP);
			
			void * argPointer = malloc(sizeof(DriveArgs));
			((DriveArgs*) argPointer) -> rotAngle = angle;
			RobotCommand::Method method;
			method.driveMethod = RobotCommand::ROTATEANGLE;
			RobotCommand command(RobotCommand::DRIVE, method, argPointer);
			robot -> setCommand(command);
		}
	}
}

float Rangefinder::wallDist() {
	ultraLeft.Ping();
	if (ultraLeft.IsRangeValid()) {
		double leftDist = ultraLeft.GetRangeInches();
		ultraRight.Ping();
		if (ultraRight.IsRangeValid()) {
			double rightDist = ultraRight.GetRangeInches();
			return ((leftDist + rightDist) / 2);
		}
	}
	return 0; // If there is an invalid range
}

void setDistToWall(float dist) {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs*) argPointer) -> driveDist = wallDist() - dist;
	RobotCommand::Method method;
	method.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand command(RobotCommand::DRIVE, method, argPointer);
	robot -> setCommand(command);
}

void runCommand(RobotCommand command)
{
	switch(command.getMethod().rangeFinderMethod)
	{
		case RobotCommand::ANGLE:
			rotateDegrees();
			break;
		case RobotCommand::SET_DIST:
			setDistToWall(command.argPointer);
			break;
	}
}
