//robot.cpp
#include "Robot.h"

Robot::Robot() :

{

}

Robot::setSpeed(){
  
  
  
}

void Robot::setCommand(Command newCommand) {
  command = newCommand;
  if (command.getSubsystem() == DRIVE) {
    driveTrain.runMethod(command.getMethod());
  }
}
