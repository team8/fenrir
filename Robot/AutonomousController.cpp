#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer)
//instance variables go here
{
	this -> robot = robotPointer;
}

void AutonomousController::startTimer(){
	time.Start();
}

void AutonomousController::drive(){
	DriveArgs* argPointer -> speedValue = ; // add some speed value
	RobotCommand command(DRIVE, SETSPEED, argPointer);
	robot -> setCommand(command);
}

void AutonomousController::stop(){
	DriveArgs * argPointer -> driveSpeed = 0;
	RobotCommand command(DRIVE, SETSPEED, argPointer);
	robot -> setCommand(command);
}

void AutonomousController::update(){
	//Runs all methods according to time
	
}
