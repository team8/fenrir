#include "Robot.h"

Robot::Robot() :
	shooter(),
	driveTrain(),
	accumulator()
{
	
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
    }
}
void Robot::update(){
	accumulator.update();
	driveTrain.update();
	shooter.update();
}
void Robot::disable(){
	driveTrain.setSpeed(0);
	accumulator.stop();
	shooter.setAllVics(0);
}
