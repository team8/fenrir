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
	/* Needs to take variables, this is just an example
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> speedValue = 23;
	Method method;
	method.driveMethod = SETSPEED;
	Command command(DRIVE, method, argPointer);
	robot -> setCommand(command);
	*/
}

void AutonomousController::stop(){
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveSpeed = 0;
	Method method;
	method.driveMethod = SETSPEED;
	RobotCommand command(DRIVE, method, argPointer);
	robot -> setCommand(command);
}

void AutonomousController::update(){
	//Runs all methods according to time
	
}
