#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer){
	std::printf("Autonomous controller constructor\n");
	this -> robot = robotPointer;
	//we shoot from about 10 feet, will modify as needed
	shootDist = 120;
	spawnDist = 200;
}

void AutonomousController::startTimer() {
	time.Start();
}

void AutonomousController::path(){
	//TODO:find the distances, and see if shoot can run simultaneously
	
	//Drive into position
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = spawnDist - shootDist; //This value is not confirmed
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);
	
	RobotCommand::Method shoot;
	shoot.shooterMethod = RobotCommand::FIRE;
	RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	robot -> setCommand(command);
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