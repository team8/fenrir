#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer)

//instance variables go here

{
  this -> robot = robotPointer;
}  

AutonomousController::startTimer(){
  
  time.start();
}

AutonomousController::drive(){
  robot.setCommand(DRIVE, /*method number*/, /*pass value*/);
  //we'll add this later
}

AutonomousController::stop(){
  robot.setCommand(DRIVE, /*method number*/, /*pass value*/);
  //we'll add this later
}

AutonomousController::update(){
  //we'll add this later
}
