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
	this-> robot = robotPointer;
} 

void HumanController::update(){
	//Here call the appropriate function from drive train

	void * argPointer = malloc(sizeof(DriveArgs));

	((DriveArgs*)argPointer) -> speedValue = getSpeedStick();
	((DriveArgs*)argPointer) -> turnValue = getTurnStick();
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::SETSPEED;
	RobotCommand command(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(command);

	if(accuButtonPrev != getAccumulatorButton()){
		if(getAccumulatorButton()){
			
			RobotCommand::Method setAccumulator;
			setAccumulator.accumulatorMethod = RobotCommand::ACCUMULATE;
			RobotCommand command(RobotCommand::ACCUMULATOR, setAccumulator, 0);
			robot -> setCommand(command);
		}
		else{
			RobotCommand::Method stopAccumulator;
			stopAccumulator.accumulatorMethod = RobotCommand::STOP;
			RobotCommand command(RobotCommand::ACCUMULATOR, stopAccumulator, 0);
			robot -> setCommand(command);
		}
	}

	if(shootButtonPrev!=getShootButton()){
		if(getShootButton()){
			RobotCommand::Method shoot;
			shoot.shooterMethod = RobotCommand::FIRE;
			RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
			robot -> setCommand(command);
		}
	}

	if(warmupButtonPrev!=getWarmupButton()){
		if(getShootButton()){
			RobotCommand::Method prep;
			prep.shooterMethod = RobotCommand::PREP;
			RobotCommand command(RobotCommand::SHOOTER, prep, 0);
			robot -> setCommand(command);
		}
	}
	if(passButtonPrev!=getPassButton()){
		if(getShootButton()){
			RobotCommand::Method pass;
			pass.accumulatorMethod = RobotCommand::PASS;
			RobotCommand command(RobotCommand::ACCUMULATOR, pass, 0);
			robot -> setCommand(command);
		}
	}
	accuButtonPrev = getAccumulatorButton();
	shootButtonPrev = getShootButton();
	warmupButtonPrev = getWarmupButton();
	passButtonPrev = getPassButton();
}

float HumanController::getSpeedStick(){
	float speed = speedStick.GetY(); 
	if (speed > 0.2 || speed < - 0.2) std::printf("Neelay Y U no...\n");
	return speed;
}

float HumanController::getTurnStick() {
	float turn = turnStick.GetX();
	if (turn > 0.2 || turn < - 0.2) std::printf("Neelay is XX\n");
	return turn;
}

float HumanController::getAccumulatorStick() {
	return operatorStick.GetY(); // For adjusting the accumulator with Operator stick
}

bool HumanController::getAccumulatorButton() {
	//return operatorStick.GetRawButton((uint32_t)ACCUMULATOR_BUTTON_PORT); // Get button to start accumulator from Operator stick
	return operatorStick.GetTrigger(); // For testing purposes
}

bool HumanController::getShootButton() {
	//return operatorStick.GetTrigger(); // Get trigger button to shoot from Operator stick
	return operatorStick.GetRawButton((uint32_t)ACCUMULATOR_BUTTON_PORT); // For testing purposes
}

bool HumanController::getWarmupButton() {
	return operatorStick.GetRawButton((uint32_t)WARMUP_BUTTON_PORT); // Get button to start shooter warmup from Operator stick
}

bool HumanController::getPassButton() {
	return operatorStick.GetRawButton((uint32_t)PASS_BUTTON_PORT);
}
