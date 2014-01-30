#include "Rangefinding.h"

Rangefinding::Rangefinding(Robot* robotPointer) :
	ultraLeft((uint32_t)ECHO_PULSE_OUT_1, (uint32_t)TRIGGER_PULSE_IN_1),
	ultraRight((uint32_t)ECHO_PULSE_OUT_2, (uint32_t)TRIGGER_PULSE_IN_2)
{
	this -> robot = robotPointer;
	ultraLeft.SetAutomaticMode(false); // Prevents sensors from automatically going off
	ultraRight.SetAutomaticMode(false);
}

void Rangefinding::rotateDegrees() {
	ultraLeft.Ping(); // Sends ping
	if (ultraLeft.IsRangeValid()) {
		double leftDist = ultraLeft.GetRangeInches();
		ultraRight.Ping();
		if (ultraRight.IsRangeValid()) {
			double rightDist = ultraRight.GetRangeInches();
			double angle = atan((leftDist - rightDist) / ULTRA_GAP);

			// Sends Command
			void * argPointer = malloc(sizeof(DriveArgs));
			((DriveArgs*) argPointer) -> rotAngle = angle;
			RobotCommand::Method method;
			method.driveMethod = RobotCommand::ROTATEANGLE;
			RobotCommand command(RobotCommand::DRIVE, method, argPointer);
			robot -> setCommand(command);
			return;
		}
		printf("Right Ultrasonic - Invalid range\n");
		return;
	}
	printf("Left Ultrasonic - Invalid range\n");
}

double Rangefinding::getDistance(){
	ultraLeft.Ping();
	int leftDist = ultraLeft.GetRangeInches();
	ultraRight.Ping();
	int rightDist = ultraRight.GetRangeInches();
	return ((leftDist + rightDist) / 2);
}
