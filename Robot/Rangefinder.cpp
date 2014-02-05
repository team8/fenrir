#include "Rangefinder.h"

Rangefinder::Rangefinder(Robot* robotPointer) :
	ultraLeft((uint32_t)ECHO_PULSE_OUT_1, (uint32_t)TRIGGER_PULSE_IN_1),
	ultraRight((uint32_t)ECHO_PULSE_OUT_2, (uint32_t)TRIGGER_PULSE_IN_2)
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

int Rangefinder::wallDist() {
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
