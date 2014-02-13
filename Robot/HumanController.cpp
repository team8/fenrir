#include "HumanController.h"
#include <stdlib.h>
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
	//Here call the appropriate function from drive train

	void * argPointer = malloc(sizeof(DriveArgs));
	
	//Using input from joystick to set values
	
	//Makes joystick less sensitive on lower end
	if(getSpeedStick()<0.75) {
		((DriveArgs*)argPointer) -> speedValue = getSpeedStick()*SPEED_SENSITIVITY;
	}
	else {
		((DriveArgs*)argPointer) -> speedValue = getSpeedStick();
	}
	
//	RobotCommand::Method setSpeed;
//	setSpeed.driveMethod = RobotCommand::SETSPEED;
//	RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
//	robot -> setCommand(speedCommand);
//	
//	((DriveArgs*)argPointer) -> rotSpeed = getTurnStick();
//	RobotCommand::Method rotSpeed;
//	rotSpeed.driveMethod = RobotCommand::ROTATESPEED;
//	RobotCommand rotateCommand(RobotCommand::DRIVE, rotSpeed, argPointer);
//	robot -> setCommand(rotateCommand);
	
	if(autoTester!=speedStick.GetTrigger() && speedStick.GetTrigger() == true) {
		
		((DriveArgs*)argPointer) -> driveDist = 1.0;
		RobotCommand::Method driveDist;
		driveDist.driveMethod = RobotCommand::DRIVEDIST;
		RobotCommand autoCommand(RobotCommand::DRIVE, driveDist, argPointer);
		robot -> setCommand(autoCommand);
		
	}

	if(getAccumulator()<-0.2) {
		RobotCommand::Method setAccumulator;
		setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
		robot -> setCommand(command);
	}
	else if(getAccumulator()>0.2){
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
	

	if(shootButtonPrev!=getShootButton()){
		if(getShootButton()){
			RobotCommand::Method shoot;
			shoot.shooterMethod = RobotCommand::FIRE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
			robot -> setCommand(command);
		}
	}

	if(getAccumulator()>0){
			RobotCommand::Method pass;
			pass.accumulatorMethod = RobotCommand::PASS;
			RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
			robot -> setCommand(command);
	}
	shootButtonPrev = getShootButton();
	warmupButtonPrev = getWarmupButton();
	autoTester = speedStick.GetTrigger();
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
	//return operatorStick.GetTrigger(); // Get trigger button to shoot from Operator stick
	return operatorStick.GetTrigger();
}

bool HumanController::getWarmupButton() {
	return operatorStick.GetRawButton((uint32_t)WARMUP_BUTTON_PORT); // Get button to start shooter warmup from Operator stick
}

