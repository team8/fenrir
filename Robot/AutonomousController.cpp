#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) {
	this -> robot = robotPointer;
	shootDist = 120; // Distance from the goal we should shoot
	spawnDist = 218; // Distance we start from the goal
	pathCalled = false;
}

void AutonomousController::path() {
	void * argPointer = malloc(sizeof(DriveArgs));
		
	// Drive
	((DriveArgs*)argPointer) -> driveDist = spawnDist - shootDist;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(speedCommand);
		
	// Shoot
	RobotCommand::Method shoot;
	shoot.shooterMethod = RobotCommand::FIRE;
	RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	robot -> setCommand(command);
}

void AutonomousController::update() {
	if (!pathCalled) {
		path();
		pathCalled = true;
	}
}
