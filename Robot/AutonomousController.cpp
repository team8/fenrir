#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) 
{
	firstCommand = true;
	std::printf("Autonomous controller constructor\n");

	this->robot = robotPointer;

}

bool AutonomousController::shoot() {
	return false;
}

/*Premade paths depending on where we start left-to-right*/
void AutonomousController::pathOne(){
	//PLS NOTE: NOT CORRECT: Use the correct commands as appropriate

	//Drive into position
	void *argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = 10; //This value is not confirmed
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);

	//Use rangefinders to calibrate exactly
//	RobotCommand::Method findRange;
//	findRange.rangefinderMhggethod = RobotCommand::WALL_DIST;
//	RobotCommand alignCommand(RobotCommand::RANGEFINDER, findRange, 0);
//	robot -> setCommand(alignCommand);
}




void AutonomousController::update() {
	if(firstCommand){
		pathOne();
		firstCommand = false;
	}
//	Runs all methods according to time
//	if(time.HasPeriodPassed(5)) { // modify time value
//		void * argPointer = malloc(sizeof(DriveArgs));
//		((DriveArgs *) argPointer) -> speedValue = 0;
//		RobotCommand::Method setSpeed;
//		setSpeed.driveMethod = RobotCommand::SETSPEED;
//		RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
//		robot -> setCommand(positionCommand);

	//	std::printf("Right: %f Left: %f \n", robot->getRightEnc(), robot->getLeftEnc());
//	}
}
