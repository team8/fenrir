#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer)

//instance variables go here

{
  this -> robot = robotPointer;
}  

void AutonomousController::startTimer(){
  
  time.Start();
}

void AutonomousController::drive(){
  void * argPointer = malloc(sizeof(DriveArgs));
  RobotCommand command(true, DRIVE, SETSPEED, argPointer);
  robot->setCommand(command);
  //we'll add this later
}

void AutonomousController::stop(){
  void * argPointer = malloc(sizeof(DriveArgs));
  ((DriveArgs *)argPointer) -> speedValue = 0;
  RobotCommand command(true, DRIVE, SETSPEED, argPointer);
  robot->setCommand(command);
  //we'll add this later
}

void AutonomousController::update(){
  //we'll add this later
}
