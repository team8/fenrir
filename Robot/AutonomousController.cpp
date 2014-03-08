#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) {
	pathCalled = false;
	std::printf("Autonomous controller constructor\n");
	this -> robot = robotPointer;
	//we shoot from about 10 feet, will modify as needed
	shootDist = 120;
	spawnDist = 218;
}

void AutonomousController::startTimer() {
	time.Start();
}

void AutonomousController::path() {
	//TODO:find the distances, and see if shoot can run simultaneously

	//Drive into position
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = spawnDist - shootDist; //This value is confirmed
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);

	//RobotCommand::Method shoot;
	//shoot.shooterMethod = RobotCommand::FIRE;
	//RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	//robot -> setCommand(command);
}

void AutonomousController::update() {
	//TODO: fix logic
	if (!pathCalled) {
		path();
		pathCalled = true;
	}
}
