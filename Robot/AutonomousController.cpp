#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer){
	std::printf("Autonomous controller constructor\n");
	this -> robot = robotPointer;
	shootDist = 0;
	spawnDist = 0;
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
	RobotCommand stopCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(stopCommand);
}

bool AutonomousController::shoot() {
	return false;
}

/*Premade paths depending on where we start left-to-right*/
void AutonomousController::path(){
	
	//Drive into position
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = spawnDist - shootDist; //This value is not confirmed
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);
	
}

void AutonomousController::update() {
//	Runs all methods according to time
//	if(time.HasPeriodPassed(5)) { // modify time value
//		void * argPointer = malloc(sizeof(DriveArgs));
//		//shootDist= will add more stuff later(the purpose of this is to find the distance until the robot is at the right distance to shoot using the angle of shot and height of goal)
//		((DriveArgs *) argPointer) -> driveDist = 5; //how far to go to get into zone
//		RobotCommand::Method driveDist;
//		driveDist.driveMethod = RobotCommand::DRIVEDIST;
//		RobotCommand command(RobotCommand::DRIVE, driveDist, argPointer);
//	}
}
