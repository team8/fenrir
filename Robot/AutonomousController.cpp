#include "AutonomousController.h"
#include "Constants.h"
#include <stdlib.h>

AutonomousController::AutonomousController(Robot *robotPointer)
//instance variables go here
{
	this -> robot = robotPointer;
	ultraLeft.SetAutomaticMode(false); // Prevents sensors from automatically going off
	ultraRight.SetAutomaticMode(false);
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

void AutonomousController::rotateDegrees() { // Returns the amount of degrees of rotation needed to be perpendicular to the wall
	ultraLeft.Ping(); // Sends ping
	if (ultraLeft.IsRangeValid()) {
		int leftDist = ultraLeft.GetRangeInches();
		ultraRight.Ping();
		if (ultraRight.IsRangeValid()) {
			int rightDist = ultraRight.GetRangeInches();
			double angle = atan((leftDist - rightDist)/ULTRA_GAP);
			
			// Sends Command
			void * argPointer = malloc(sizeof(DriveArgs));
			((DriveArgs *) argPointer) -> rotAngle = angle;
			Method method;
			method.driveMethod = ROTATEANGLE;
			Command command(DRIVE, method, argPointer);
			robot -> setCommand(command);
			return;
		}
		printf("Right Ultrasonic - Invalid range\n");
		return;
	}
	printf("Left Ultrasonic - Invalid range\n");
}
