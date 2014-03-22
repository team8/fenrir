#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) {
	this -> robot = robotPointer;
	shootDist = 120;
	spawnDist = 218;
	time.Stop();
	time.Reset();
}

void AutonomousController::path() {
	void * argPointer = malloc(sizeof(DriveArgs));

	//if(robot->getLeftEnc()!= 45 && robot->getRightEnc() != 45) {
	//double average = (robot->getLeftEnc() + robot->getRightEnc())/2;
		
	((DriveArgs*)argPointer) -> driveDist = 20;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(speedCommand);
}

void AutonomousController::init() {
	path();
}

void AutonomousController::update() {
	/*BACKUP CODE*/
//	time.Start();
//	if(time.Get() < 3) {
//		void * argPointer = malloc(sizeof(DriveArgs));
//		((DriveArgs *) argPointer) -> speedValue = -0.3;
//		RobotCommand::Method setSpeed;
//		setSpeed.driveMethod = RobotCommand::SETSPEED;
//		RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
//		robot -> setCommand(positionCommand);
//	}
//	else {
//		void * argPointer = malloc(sizeof(DriveArgs));
//		((DriveArgs *) argPointer) -> speedValue = 0;
//		RobotCommand::Method setSpeed;
//		setSpeed.driveMethod = RobotCommand::SETSPEED;
//		RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
//		robot -> setCommand(positionCommand);
		
	//	std::printf("Right: %f Left: %f \n", robot->getRightEnc(), robot->getLeftEnc());
//	}

}
