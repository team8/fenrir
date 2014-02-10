#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer)
{
	this -> robot = robotPointer;
}  

void AutonomousController::startTimer() {
	time.Start();
}


void AutonomousController::drive(float v) {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveSpeed = v;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::SETSPEED;
	RobotCommand command(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(command);
}

void AutonomousController::stop() {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveSpeed = 0;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::SETSPEED;
	RobotCommand command(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(command);
}

bool AutonomousController::shoot() {
	
}

void AutonomousController::update() {
	//Runs all methods according to time
	if(time.Get() <= 5) { // modify time value
		void * argPointer = malloc(sizeof(DriveArgs));
		//shootDist= will add more stuff later(the purpose of this is to find the distance until the robot is at the right distance to shoot using the angle of shot and height of goal)
		((DriveArgs *) argPointer) -> driveDist = 5; //how far to go to get into zone
		RobotCommand::Method driveDist;
		driveDist.driveMethod = RobotCommand::DRIVEDIST;
		RobotCommand command(RobotCommand::DRIVE, driveDist, argPointer);
	}
}
