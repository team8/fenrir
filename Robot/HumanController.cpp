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
	operatorStick(PORT_OPERATOR),
	xbox((uint32_t)PORT_SPEED)
{  
	prevStop = false;
	prevZ = false;
	this-> robot = robotPointer;
	joystick = false;
} 

void HumanController::update() {
	void * argPointer = malloc(sizeof(DriveArgs));

	if (speedStick.GetTrigger()) {
		RobotCommand::Method findRange;
		findRange.rangefinderMethod = RobotCommand::WALL_DIST;
		RobotCommand command(RobotCommand::RANGEFINDER, findRange, 0);
		robot -> setCommand(command);
	}

	if(abs(getTurnStick())<=.1 && abs(getSpeedStick())<=.1) {
		//TODO: ask ahmed if he want to be able to move forward but not turn at small speeds
		((DriveArgs*)argPointer)->speedValue = getSpeedStick();
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
	if(abs(getSpeedStick())>0.1){
		((DriveArgs*)argPointer)->speedValue = getSpeedStick();
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot -> setCommand(speedCommand);
	}

	if(abs(getTurnStick())>0.1){
		((DriveArgs*)argPointer) -> rotSpeed = getTurnStick();
		RobotCommand::Method rotSpeed;
		rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
		robot -> setCommand(rotateCommand);
	}

	/*ACCUMULATOR*/
	if(getAccumulator()<-0.2) {
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot -> setCommand(command);
		prevStop = false;
	}
	else if(getAccumulator()>0.2) {
		RobotCommand::Method pass;
		pass.accumulatorMethod = RobotCommand::PASS;
		RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
		robot -> setCommand(command);
		RobotCommand::Method eject;
		eject.shooterMethod = RobotCommand::EJECT;
		RobotCommand ejectCommand(RobotCommand::SHOOTER, eject, 0);
		robot -> setCommand(ejectCommand);

	}
	else {
		RobotCommand::Method stopAccumulator;
		stopAccumulator.accumulatorMethod = RobotCommand::STOP;
		RobotCommand command(RobotCommand::ACCUMULATOR, stopAccumulator, 0);
		robot -> setCommand(command);
		if(!prevStop) {
			std::printf("idling after accumulator\n");
			RobotCommand::Method idle;
			idle.shooterMethod = RobotCommand::IDLE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
			robot -> setCommand(command);
		}
		prevStop = true;
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

		}
		else if (!prevZ) {
			std::printf("shut off manual\n");
			RobotCommand::Method idle;
			idle.shooterMethod = RobotCommand::IDLE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
			robot -> setCommand(command);
		}

	if(shootButtonPrev!=getShootButton()){
		if(getShootButton()){
			((DriveArgs*)argPointer)->driveDist = 10;
			RobotCommand::Method align;
			align.rangefinderMethod = RobotCommand::SET_DIST;
			RobotCommand alignCommand(RobotCommand::RobotCommand::RANGEFINDER, align, 0);
			robot -> setCommand(alignCommand);
			RobotCommand::Method shoot;
			shoot.shooterMethod = RobotCommand::MANUAL_LOAD;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
			robot -> setCommand(command);
		}
		prevZ = false;
	}

	if(!prevRangeButton && getRangeButton()){
		RobotCommand::Method rangefind;
		rangefind.rangefinderMethod = RobotCommand::WALL_DIST;
		RobotCommand rangeCommand(RobotCommand::RobotCommand::RANGEFINDER, rangefind, 0);
		robot -> setCommand(rangeCommand);
	}	

	shootButtonPrev = getShootButton();
	lastFlushTrigger = getFlushTrigger();
	prevRangeButton = getRangeButton(); 
}

double HumanController::getSpeedStick(){
	if (joystick) {
		return (speedStick.GetY());
	} else {
		return xbox.getLeftY();
	}
}

double HumanController::getTurnStick() {
	if (joystick) {
		return turnStick.GetX();
	} else {
		return xbox.getRightX();
	}
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
//	return false;
	return operatorStick.GetRawButton((uint_t)3);
}

bool HumanController::getFlushTrigger() {
	//flush out the ball
	return operatorStick.GetRawButton((uint32_t)FLUSH_TRIGGER);
}
double HumanController::getOperatorZ() {
	return operatorStick.GetThrottle();
}
bool HumanController::getRangeButton() {
	return operatorStick.GetRawButton((uint32_t)4);
}	
