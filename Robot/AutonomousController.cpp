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
	DriveArgs* argPointer -> speedValue = 23;
	Command command(DRIVE, SETSPEED, argPointer);
	robot -> setCommand(command);
}

void AutonomousController::stop(){
	/* void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveSpeed = 0;
	Method method;
	method.driveMethod = SETSPEED;
	RobotCommand command(DRIVE, method, argPointer);
	robot -> setCommand(command);
	*/
	
}

void AutonomousController::update(){
	//Runs all methods according to time
	
}
