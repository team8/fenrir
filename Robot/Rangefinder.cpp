#include "Rangefinder.h"

Rangefinder::Rangefinder(Robot* robotPointer) :
	ultraLeft((uint32_t)ULTRASONIC_CHANNEL_LEFT), // We need to figure out what channels are and give it a value
	ultraRight((uint32_t)ULTRASONIC_CHANNEL_RIGHT)
{
	this -> robot = robotPointer;
}

void Rangefinder::rotateToWall() {
	double leftDist = ultraLeft.GetVoltage(); // This might be wrong, it might be GetValue()
	double rightDist = ultraRight.GetVoltage();
	double angle = atan((leftDist - rightDist) / ULTRA_GAP);
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs*) argPointer) -> rotAngle = angle;
	RobotCommand::Method method;
	method.driveMethod = RobotCommand::ROTATEANGLE;
	RobotCommand command(RobotCommand::DRIVE, method, argPointer);
	robot -> setCommand(command);
}

float Rangefinder::wallDist() {
	double leftDist = ultraLeft.GetVoltage(); // This might be wrong, it might be GetValue()
	double rightDist = ultraRight.GetVoltage();
	return ((leftDist + rightDist) / 2); // The distance to the wall from the middle of the robot
}

void Rangefinder::setDistToWall(float dist) {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs*) argPointer) -> driveDist = wallDist() - dist;
	RobotCommand::Method method;
	method.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand command(RobotCommand::DRIVE, method, argPointer);
	robot -> setCommand(command);
}

void Rangefinder::runCommand(RobotCommand command) {
	RangefinderArgs* args = (RangefinderArgs*) command.argPointer;
	switch(command.getMethod().rangefinderMethod) {
		case RobotCommand::ANGLE:
			rotateToWall();
			break;
		case RobotCommand::SET_DIST:
			setDistToWall(args -> target);
			break;
	}
}
