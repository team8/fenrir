//robot.cpp
#include "Robot.h"

Robot::Robot()
{

}

void Robot::setCommand(RobotCommand command) {
    switch (command.getSubsystem()) {
        case DRIVE:
            driveTrain.runMethod(command);
            break;
        case SHOOTER:
            shooter.runMethod(command);
            break;
        case ACCUMULATOR:
            accumulator.runMethod(command);
    }
}
