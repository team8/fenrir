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
  void * argPointer = malloc(sizeof(DriveArgs));
  argPointer -> /*parameter*/ = /*Enter any number here*/;
  robot.setCommand(Command command(true, DRIVE, /*Method*/, argPointer));
  //we'll add this later
}

AutonomousController::stop(){
  void * argPointer = malloc(sizeof(DriveArgs));
  argPointer -> driveSpeed = 0;
  robot.setCommand(Command command(true, DRIVE, DRIVESPEED, argPointer));
  //we'll add this later
}

AutonomousController::update(){
  //we'll add this later
}
