#include "HumanController.h"
#include <stdlib.h>
#include <cmath>
/* Command example - How to issue commands
 void * argPointer = malloc(sizeof(DriveArgs)); //this lets you access the drive args stored in command
 argPointer -> variable in DriveArgs = Enter parameter here; //this lets you set a variable to what you want
 robot.setCommand(Command command(false, DRIVE, Method, argPointer)); //replace Method with appropriate method
 */

HumanController::HumanController(Robot *robotPointer) :
#if defined JOYSTICK_CONTROLS
			speedStick((uint32_t) PORT_SPEED), 
			turnStick((uint32_t) PORT_TURN), 
			operatorStick((uint32_t) PORT_OPERATOR)
#elif defined XBOX_CONTROLS
			xbox((uint32_t)PORT_XBOX)
#endif
{
#ifdef JOYSTICK_CONTROLS
	prevZ = false;
	prevStop = false;
	lastOutButton = false;
	lastManualFireButton = false;
	lastManualLoadButton = false;
	manualControl = false;
	lastManualButton = false;
#endif
	this->robot = robotPointer;
}

void HumanController::update() {
	void *argPointer = malloc(sizeof(DriveArgs));

#ifdef JOYSTICK_CONTROLS
	//	if (speedStick.GetTrigger()) {
	//		RobotCommand::Method findRange;
	//		findRange.rangefinderMethod = RobotCommand::WALL_DIST;
	//		RobotCommand command(RobotCommand::RANGEFINDER, findRange, 0);
	//		robot->setCommand(command);
	//	}
#endif

	if (abs(getTurnStick()) <= .1 && abs(getSpeedStick()) <= .1) {

		((DriveArgs*) argPointer)->speedValue = getSpeedStick();
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot->setCommand(speedCommand);

		((DriveArgs*) argPointer) -> rotSpeed = 0;
		RobotCommand::Method rotSpeed;
		rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
		robot->setCommand(rotateCommand);
	}
	if (abs(getSpeedStick()) > 0.1) {
		((DriveArgs*) argPointer)->speedValue = getSpeedStick();
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot->setCommand(speedCommand);
	}

	if (abs(getTurnStick()) > 0.1) {
		((DriveArgs*) argPointer) -> rotSpeed = getTurnStick();
		RobotCommand::Method rotSpeed;
		rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
		robot->setCommand(rotateCommand);
	}

	/*ACCUMULATOR Joystick Controls*/
#if defined JOYSTICK_CONTROLS
	if (getAccumulatorStick() < -0.2) {
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot->setCommand(command);
//		prevStop = false;
	} else if (getAccumulatorStick() > 0.2) {

		RobotCommand::Method pass;
		pass.accumulatorMethod = RobotCommand::PASS;
		RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
		robot->setCommand(command);

	} else {
		RobotCommand::Method stopAccumulator;
		stopAccumulator.accumulatorMethod = RobotCommand::STOP;
		RobotCommand command(RobotCommand::ACCUMULATOR, stopAccumulator, 0);
		robot->setCommand(command);
//		if (!prevStop) {
//			RobotCommand::Method idle;
//			idle.shooterMethod = RobotCommand::IDLE;
//			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
//			robot->setCommand(command);
//		}
//		prevStop = true;
	}
#endif

	/*ACCUMULATOR XBox Controls*/
#if defined XBOX_CONTROLS
	if(xbox.getButtonLB() && !xbox.getButtonRB()) { //FLUSH/PASS
		RobotCommand::Method pass;
		pass.accumulatorMethod = RobotCommand::PASS;
		RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
		robot->setCommand(command);
	} else if(xbox.getButtonRB() && !xbox.getButtonLB()) { //ACCUMULATE
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot->setCommand(command);
	} else { //IDLE
		RobotCommand::Method stopAccumulator;
		stopAccumulator.accumulatorMethod = RobotCommand::STOP;
		RobotCommand command(RobotCommand::ACCUMULATOR, stopAccumulator, 0);
		robot->setCommand(command);
	}
#endif

	/*FLUSH Joystick Controls*/
#ifdef JOYSTICK_CONTROLS
	if (getFlushTrigger()) {
		/*ACCUMULATOR_FLUSH/PASS Joystick Controls*/
//		RobotCommand::Method accuFlush;
//		accuFlush.accumulatorMethod = RobotCommand::PASS;
//		RobotCommand accuFlushCommand(RobotCommand::ACCUMULATOR, accuFlush, 0);
//		robot->setCommand(accuFlushCommand);

		/*SHOOTER_FLUSH Joystick Controls*/
		std::printf("Flush\n");
		RobotCommand::Method shooterFlush;
		shooterFlush.shooterMethod = RobotCommand::FLUSH;
		RobotCommand shooterFlushCommand(RobotCommand::SHOOTER, shooterFlush, 0);
		robot->setCommand(shooterFlushCommand);

	}
	else if(getFlushOutButton()) {
//		RobotCommand::Method outFlushAccum;
//		outFlushAccum.accumulatorMethod = RobotCommand::ACCUMULATE;
//		RobotCommand outAccumCommand(RobotCommand::ACCUMULATOR, outFlushAccum, 0);
//		robot->setCommand(outAccumCommand);
		std::printf("outFlushing\n");
		RobotCommand::Method outFlushShooter;
		outFlushShooter.shooterMethod = RobotCommand::OUT_FLUSH;
		RobotCommand outShooterCommand(RobotCommand::SHOOTER, outFlushShooter, 0);
		robot->setCommand(outShooterCommand);
	}
	else if ((!getFlushTrigger() && lastFlushTrigger) || (!getFlushOutButton() && lastOutButton)) { //Idle 

		RobotCommand::Method accuStop;
		accuStop.accumulatorMethod = RobotCommand::STOP;
		RobotCommand accuFlushCommand(RobotCommand::ACCUMULATOR, accuStop, 0);
		robot->setCommand(accuFlushCommand);

		RobotCommand::Method shooterIdle;
		shooterIdle.shooterMethod = RobotCommand::IDLE;
		RobotCommand shooterIdleCommand(RobotCommand::SHOOTER, shooterIdle, 0);
		robot->setCommand(shooterIdleCommand);

	}
#endif

	/*SHOOTER Joystick Controls*/
#ifdef JOYSTICK_CONTROLS
	if(getManualButton() && !lastManualButton) {
		if(manualControl) {
			manualControl = false;
		}
		else {
			manualControl = true;
		}
	}
	if(!manualControl) {
		if (shootButtonPrev != getShootButton() && getShootButton()) {
			RobotCommand::Method shoot;
			shoot.shooterMethod = RobotCommand::FIRE;
			RobotCommand shootCommand(RobotCommand::SHOOTER, shoot, 0);
			robot->setCommand(shootCommand);
			std::printf("firing\n");
		} 
		
	}else {
			if(getManualFireButton()) {
				RobotCommand::Method manualFire;
				manualFire.shooterMethod = RobotCommand::MANUAL_FIRE;
				RobotCommand fireCommand(RobotCommand::SHOOTER, manualFire, 0);
				robot->setCommand(fireCommand);
			}
			if(getManualLoadButton() && getManualFireButton()) {
					RobotCommand::Method manualLoad;
					manualLoad.shooterMethod = RobotCommand::MANUAL_LOAD;
					RobotCommand loadCommand(RobotCommand::SHOOTER, manualLoad, 0);
					robot->setCommand(loadCommand);
				}
			if(!getManualFireButton()&& !getManualLoadButton() && !getFlushTrigger() && !getFlushOutButton()) {
				RobotCommand::Method idle;
				idle.shooterMethod = RobotCommand::IDLE;
				RobotCommand fireCommand(RobotCommand::SHOOTER, idle, 0);
				robot->setCommand(fireCommand);
			}
	}

		
	/*SHOOTER XBox Controls*/
#elif defined XBOX_CONTROLS
	if (getShootButton() == 1) { //FLUSH
		RobotCommand::Method shooterFlush;
		shooterFlush.shooterMethod = RobotCommand::FLUSH;
		RobotCommand shooterFlushCommand(RobotCommand::SHOOTER, shooterFlush, 0);
		robot->setCommand(shooterFlushCommand);
		prevShoot = true;
	}
	else if (getShootButton() == -1) { //SHOOT
		RobotCommand::Method fireCommand;
		fireCommand.shooterMethod = RobotCommand::FIRE;
		RobotCommand command(RobotCommand::RobotCommand::SHOOTER, fireCommand, 0);
		robot->setCommand(command);
		prevShoot = false;
	}
	else if(prevShoot && getShootButton() == 0) { //IDLE
		RobotCommand::Method idle;
		idle.shooterMethod = RobotCommand::IDLE;
		RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
		robot->setCommand(command);
	}
#endif

#ifdef JOYSTICK_CONTROLS
	lastFlushTrigger = getFlushTrigger();
	//prevRangeButton = getRangeButton(); 
	lastManualFireButton = getManualFireButton();
	lastManualLoadButton = getManualLoadButton();
	lastOutButton = getFlushOutButton();
	lastManualButton = getManualButton();
#endif
	shootButtonPrev = getShootButton();
}

double HumanController::getSpeedStick() {
#if defined JOYSTICK_CONTROLS
	return speedStick.GetY();
#elif defined XBOX_CONTROLS
	return xbox.getLeftY();
#endif
}

double HumanController::getTurnStick() {
#if defined JOYSTICK_CONTROLS
	return turnStick.GetX();
#elif defined XBOX_CONTROLS
	return xbox.getRightX();
#endif
}

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
	return operatorStick.GetRawButton((uint32_t) 4);
}

double HumanController::getOperatorZ() {
	return operatorStick.GetThrottle();
}

bool HumanController::getManualFireButton() {
	return operatorStick.GetTrigger();
}
bool HumanController::getManualLoadButton() {
	return operatorStick.GetRawButton((uint32_t) 2);
}
double HumanController::getFlushOutButton() {
	return operatorStick.GetRawButton((uint32_t)3);
}
bool HumanController::getManualButton() {
	return operatorStick.GetRawButton((uint32_t)6);
}
#endif
