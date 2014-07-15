#include "HumanController.h"
#include <stdlib.h>
#include <cmath>
/* Command example - How to issue commands
  void * argPointer = malloc(sizeof(DriveArgs)); //this lets you access the drive args stored in command
  argPointer -> variable in DriveArgs = Enter parameter here; //this lets you set a variable to what you want
  robot.setCommand(Command command(false, DRIVE, Method, argPointer)); //replace Method with appropriate method
 */

HumanController::HumanController(Robot *robotPointer):
#if defined JOYSTICK_CONTROLS
	speedStick(PORT_SPEED),
	turnStick(PORT_TURN),
	operatorStick(PORT_OPERATOR)
#elif defined XBOX_CONTROLS
	xbox((uint32_t)PORT_SPEED)
#endif
{  
	prevStop = false;
	this-> robot = robotPointer;
} 

void HumanController::update() {
	void * argPointer = malloc(sizeof(DriveArgs));

#ifdef JOYSTICK_CONTROLS
	if (speedStick.GetTrigger()) {
		RobotCommand::Method findRange;
		findRange.rangefinderMethod = RobotCommand::WALL_DIST;
		RobotCommand command(RobotCommand::RANGEFINDER, findRange, 0);
		robot -> setCommand(command);
	}
#endif

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

	/*ACCUMULATOR Joystick Controls*/
#if defined JOYSTICK_CONTROLS
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
			RobotCommand::Method idle;
			idle.shooterMethod = RobotCommand::IDLE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
			robot -> setCommand(command);
		}
		prevStop = true;
	}
#endif

	/*ACCUMULATOR XBox Controls*/
#if defined XBOX_CONTROLS
	if(xbox.getButtonLB() && !xbox.getButtonRB()) {
		RobotCommand::Method pass;
		pass.accumulatorMethod = RobotCommand::PASS;
		RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
		robot -> setCommand(command);
	}
	else if(!xbox.getButtonLB() && xbox.getButtonRB()) {
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot -> setCommand(command);
	}
	else {
		RobotCommand::Method stopAccumulator;
		stopAccumulator.accumulatorMethod = RobotCommand::STOP;
		RobotCommand command(RobotCommand::ACCUMULATOR, stopAccumulator, 0);
		robot -> setCommand(command);
	}
#endif
	
	/*SHOOTER*/
#if defined JOYSTICK_CONTROLS

#elif defined XBOX_CONTROLS
	if (getShootButton() == 1) {
		RobotCommand::Method shooterFlush;
		shooterFlush.shooterMethod = RobotCommand::FLUSH;
		RobotCommand shooterFlushCommand(RobotCommand::SHOOTER, shooterFlush, 0);
		robot -> setCommand(shooterFlushCommand);
		prevShoot = true;
	}
	else if (getShootButton() == -1) {
		RobotCommand::Method fireCommand;
		fireCommand.shooterMethod = RobotCommand::FIRE;
		RobotCommand command(RobotCommand::RobotCommand::SHOOTER, fireCommand, 0);
		robot -> setCommand(command);
		prevShoot = false;
	}
	else if(prevShoot && getShootButton() == 0) {
		RobotCommand::Method idle;
		idle.shooterMethod = RobotCommand::IDLE;
		RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
		robot -> setCommand(command);
	}
#endif

#ifdef JOYSTICK_CONTROLS
	lastFlushTrigger = getFlushTrigger();
	prevRangeButton = getRangeButton(); 
#endif
	shootButtonPrev = getShootButton();
}

#if defined JOYSTICK_CONTROLS
double HumanController::getSpeedStick() {
	return speedStick.GetY();
}

#elif defined XBOX_CONTROLS
double HumanController::getSpeedStick() {
	return xbox.getLeftY();
}
#endif

#if defined JOYSTICK_CONTROLS
double HumanController::getTurnStick() {
	return turnStick.GetX();
}

#elif defined XBOX_CONTROLS
double HumanController::getTurnStick() {
	return xbox.getRightX();
}
#endif

#ifdef JOYSTICK_CONTROLS
double HumanController::getAccumulatorStick() {
	return operatorStick.GetY(); // For adjusting the accumulator with Operator stick
}
#endif

#if defined JOYSTICK_CONTROLS
bool HumanController::getShootButton() {
	return operatorStick.GetTrigger();
}

#elif defined XBOX_CONTROLS
int HumanController::getShootButton() {
	if (xbox.getTrigger() > 0.5) {
		return 1;
	} else if (xbox.getTrigger() < -0.5) {
		return -1;
	} else {
		return 0;
	}
}
#endif

#ifdef JOYSTICK_CONTROLS
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
#endif