//robot.cpp
#include "Robot.h"

Robot::Robot() :

{

}

Robot::setSpeed(){
  
  
  
}

void Robot::setCommand(Command command) {
  if (command.getSubsystem() == DRIVE) {
    driveTrain.runMethod(command);
  }
}
