#include "Robot.h"

Robot::Robot() :
	driveTrain(), 
	shooter(), 
	accumulator(), 
	rangefinder() 
{
	std::printf("Robot constructor\n");
}

void Robot::setCommand(RobotCommand command) {
	switch (command.getSubsystem()) {
		case RobotCommand::DRIVE:
			driveTrain.runCommand(command);
		break;
		case RobotCommand::SHOOTER:
			shooter.runCommand(command);
		break;
		case RobotCommand::ACCUMULATOR:
			accumulator.runCommand(command);
		break;
		case RobotCommand::RANGEFINDER:
			rangefinder.runCommand(command);
		break;
		case RobotCommand::ROBOT:
			runCommand(command);
		break;
	}
}
void Robot::update() {
	accumulator.update();
	driveTrain.update();
	shooter.update();
	rangefinder.update();
}
void Robot::disable() {
	driveTrain.disable();
	shooter.setAllVics(0);
	accumulator.disable();
}

void Robot::runCommand(RobotCommand command) {
	//switch(command.getMethod().robotMethod)
	//{
	//case ALIGN_THEN_SHOOT:
	//}
}

void Robot::init() {
	driveTrain.init();
}

double Robot::getRightEnc() {
	return driveTrain.getRightEnc();
}

double Robot::getLeftEnc() {
	return driveTrain.getLeftEnc();
}
