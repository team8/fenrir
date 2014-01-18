//robot.cpp
#include "Robot.h"

Robot::Robot()
{

}

void Robot::setCommand(RobotCommand command) {
  if (command.getSubsystem() == DRIVE) {
    driveTrain.runMethod(command);
  } else if(command.getSubsystem() == SHOOTER) {
   // shooter.runMethod(command);
  }
}
