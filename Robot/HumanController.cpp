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
	prevStop = false;
	prevZ = false;
	this-> robot = robotPointer;
} 

void HumanController::update() {
	void * argPointer = malloc(sizeof(DriveArgs));
	
	/*SLIGHT MOVEMENT*/
	if(getAbsTurnStick()<=.1 && getAbsSpeedStick()<=.1) {
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
	/*FULL MOVEMENT*/
	if(getAbsSpeedStick()>0.1) {
		((DriveArgs*)argPointer)->speedValue = speedStick.GetY();
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot -> setCommand(speedCommand);
	}
	if(getAbsTurnStick()>0.1) {
		((DriveArgs*)argPointer) -> rotSpeed = turnStick.GetX();
		RobotCommand::Method rotSpeed;
		rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
		robot -> setCommand(rotateCommand);
	}
	
	/*ACCUMULATOR*/
	if(getAccumulator()<-0.2) {
		std::printf("accumulating\n");
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot -> setCommand(command);
		prevStop = false;
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
		prevStop = false;
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
	
	/*FLUSHING*/
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
	else if (!getFlushTrigger() && lastFlushTrigger) {
		RobotCommand::Method accumuStop;
		accumuStop.accumulatorMethod = RobotCommand::STOP;
		RobotCommand accuFlushCommand(RobotCommand::ACCUMULATOR, accumuStop, 0);
		robot -> setCommand(accuFlushCommand);

		RobotCommand::Method shootStop;
		shootStop.shooterMethod = RobotCommand::IDLE;
		RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shootStop, 0);
		robot -> setCommand(command);
	}
	
	/*SHOOTER*/
	if(getOperatorZ() < 0.5) {
		if(shootButtonPrev!=getShootButton() && getShootButton()){
			
			((DriveArgs*) argPointer)->driveDist = 10;

			RobotCommand::Method shoot;
			shoot.shooterMethod = RobotCommand::FIRE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
			robot -> setCommand(command);
		}
		else if (!prevZ) {
			std::printf("shut off manual\n");
			RobotCommand::Method idle;
			idle.shooterMethod = RobotCommand::IDLE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, idle, 0);
			robot -> setCommand(command);
		}
		prevZ = true;
	}
	else if(getOperatorZ() > 0.5) {
		std::printf("is in manual\n");
		RobotCommand::Method shoot;
		shoot.shooterMethod = RobotCommand::MANUAL_FIRE;
		RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
		robot -> setCommand(command);
		
		if(getShootButton()) {
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

double HumanController::getAbsSpeedStick(){
	double speed = abs(speedStick.GetY());
	return speed;
}

double HumanController::getAbsTurnStick() {
	double turn = abs(turnStick.GetX());
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



