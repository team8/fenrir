#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer)
{
	std::printf("Autonomous controller constructor\n");
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
	return false;
}

// chris wanted us to add in premade paths, in here, create commands and then call them in the update method to 
//execute commands :D
void pathOne(){
	
	
}

void pathTwo() {
	
}

void pathThree() {
	
}

void AutonomousController::update() {
	//Runs all methods according to time
//	if(time.HasPeriodPassed(5)) { // modify time value
//		void * argPointer = malloc(sizeof(DriveArgs));
//		//shootDist= will add more stuff later(the purpose of this is to find the distance until the robot is at the right distance to shoot using the angle of shot and height of goal)
//		((DriveArgs *) argPointer) -> driveDist = 5; //how far to go to get into zone
//		RobotCommand::Method driveDist;
//		driveDist.driveMethod = RobotCommand::DRIVEDIST;
//		RobotCommand command(RobotCommand::DRIVE, driveDist, argPointer);
//	}
}
