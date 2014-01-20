//robot.cpp
#include "Robot.h"

Robot::Robot()
{

}

void Robot::setCommand(RobotCommand command) {
    switch (command.getSubsystem()) {
        case DRIVE:
            driveTrain.runCommand(command);
            break;
        case SHOOTER:
            shooter.runCommand(command);
            break;
        case ACCUMULATOR:
            accumulator.runCommand(command);
            break;
    }
}
