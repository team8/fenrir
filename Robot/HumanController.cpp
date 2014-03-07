#include "HumanController.h"
#include <stdlib.h>
#include <cmath>
/* Command example - How to issue commands
  void * argPointer = malloc(sizeof(DriveArgs)); //this lets you access the drive args stored in command
  argPointer -> variable in DriveArgs = Enter parameter here; //this lets you set a variable to what you want
  robot.setCommand(Command command(false, DRIVE, Method, argPointer)); //replace Method with appropriate method
 */

HumanController::HumanController(Robot *robotPointer):
	speedStick(PORT_SPEED),
	turnStick(PORT_TURN),
	operatorStick(PORT_OPERATOR)
{  
	std::printf("Human controller constructor\n");
	this-> robot = robotPointer;
} 

void HumanController::update(){
	
	void * argPointer = malloc(sizeof(DriveArgs));
//	
//	((DriveArgs*)argPointer)->driveDist = 10;
//	RobotCommand::Method driveDist;
//	driveDist.driveMethod = RobotCommand::SETSPEED;
//	RobotCommand speedCommand(RobotCommand::DRIVE, driveDist, argPointer);
//	robot -> setCommand(speedCommand);
	
	if(abs(turnStick.GetX())<=.1 && abs(speedStick.GetY())<=.1){
		((DriveArgs*)argPointer)->speedValue = speedStick.GetY();
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot -> setCommand(speedCommand);
		((DriveArgs*)argPointer) -> rotSpeed = 0;
		RobotCommand::Method rotSpeed;
		rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
		robot -> setCommand(rotateCommand);
	}
	if(abs(speedStick.GetY())>0.01){
	((DriveArgs*)argPointer)->speedValue = getSpeedStick();
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::SETSPEED;
	RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(speedCommand);
	}

	if(abs(turnStick.GetX())>0.01){
	((DriveArgs*)argPointer) -> rotSpeed = getTurnStick();
	RobotCommand::Method rotSpeed;
	rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
	RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
	robot -> setCommand(rotateCommand);
	}
	if(getAccumulator()<-0.2) {
		std::printf("accumulating\n");
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot -> setCommand(command);
	}
	else if(getAccumulator()>0.2) {
		RobotCommand::Method eject;
		eject.shooterMethod = RobotCommand::EJECT;
		RobotCommand ejectCommand(RobotCommand::SHOOTER, eject, 0);
		robot -> setCommand(ejectCommand);
		
		RobotCommand::Method pass;
		pass.accumulatorMethod = RobotCommand::PASS;
		RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
		robot -> setCommand(command);
	}
	else {
		RobotCommand::Method stopAccumulator;
		stopAccumulator.accumulatorMethod = RobotCommand::STOP;
		RobotCommand command(RobotCommand::ACCUMULATOR, stopAccumulator, 0);
		robot -> setCommand(command);
	}
	
		if (getFlushTrigger()) {
			RobotCommand::Method accumuFlush;
			accumuFlush.accumulatorMethod = RobotCommand::PASS;
			RobotCommand accuFlushCommand(RobotCommand::ACCUMULATOR, accumuFlush, 0);
			robot -> setCommand(accuFlushCommand);
			
			RobotCommand::Method shooterFlush;
			shooterFlush.shooterMethod = RobotCommand::FLUSH;
			RobotCommand shooterFlushCommand(RobotCommand::SHOOTER, shooterFlush, 0);
			robot -> setCommand(shooterFlushCommand);
			
			lastFlushTrigger = true;
		}
		else if (!getFlushTrigger() && lastFlushTrigger) {
			RobotCommand::Method accumuStop;
			accumuStop.accumulatorMethod = RobotCommand::STOP;
			RobotCommand accuFlushCommand(RobotCommand::ACCUMULATOR, accumuStop, 0);
			robot -> setCommand(accuFlushCommand);
			
			//stop shooter as well
			RobotCommand::Method shootStop;
			shootStop.shooterMethod = RobotCommand::IDLE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shootStop, 0);
			robot -> setCommand(command);
			
			lastFlushTrigger = false;
		}

	if(shootButtonPrev!=getShootButton()){
		if(getShootButton()){
			((DriveArgs*)argPointer)->driveDist = 10;

			RobotCommand::Method findRange;
			findRange.rangefinderMethod = RobotCommand::WALL_DIST;
			RobotCommand alignCommand(RobotCommand::RANGEFINDER, findRange, 0);
			robot -> setCommand(alignCommand);
			
			RobotCommand::Method shoot;
			shoot.shooterMethod = RobotCommand::FIRE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
			robot -> setCommand(command);
		}
	}
	shootButtonPrev = getShootButton();
	lastFlushTrigger = getFlushTrigger();
}

double HumanController::getSpeedStick(){
	double speed = speedStick.GetY(); 
	return speed;
}

double HumanController::getTurnStick() {
	double turn = turnStick.GetX();
	return turn;
}

double HumanController::getAccumulatorStick() {
	return operatorStick.GetY(); // For adjusting the accumulator with Operator stick
}

double HumanController::getAccumulator() {
	//return operatorStick.GetRawButton((uint32_t)ACCUMULATOR_BUTTON_PORT); // Get button to start accumulator from Operator stick
	return operatorStick.GetY(); // For testing purposes
}

bool HumanController::getShootButton() {
	// Get trigger button to shoot from Operator stick
	return operatorStick.GetTrigger();
}

bool HumanController::getFlushTrigger() {
	//flush out the ball
	return operatorStick.GetRawButton((uint32_t)FLUSH_TRIGGER);
}
