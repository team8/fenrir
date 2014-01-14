#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer)

//instance variables go here

{
  newCommand = false;
  this -> robot = robotPointer;
}  

AutonomousController::startTimer(){
  
  time.start();
}

AutonomousController::drive(){
  
  //we'll add this later
  
}

AutonomousController::stop(){
  
  //we'll add this later
  
}

AutonomousController::update(){
  
  //we'll add this later
  
}

Command AutonomousController::getCommand() { // For sending the command to Fenrir.cpp
  if (newCommand) {
    newCommand = false;
    return command;
  } else return NULL;
}
