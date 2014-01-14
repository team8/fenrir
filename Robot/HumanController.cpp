#include "HumanController.h"

HumanController::HumanController(Robot *robotPointer)

  //

  operatorStick(PORT_OPERATOR);
  turnStick(PORT_TURN);
  speedStick(PORT_SPEED);
  
{  
  newCommand = false;
  this-> robot = robotPointer;
}

HumanController::update() {
    //Joystick.GetY() returns value b/w -1 and 1
    
    //takes the input from the joysticks 
    float speed = speedStick.GetY(); 
    float turn = turnStick.GetX(); 
    float input = speed - turn;
    
    leftFrontVic.Set(-input);
    leftBackVic.Set(-input);
    rightFrontVic.Set(input);
    rightBackVic.Set(input); 

}

Command HumanController::getCommand() { // For sending the command to Fenrir.cpp
  if (newCommand) {
    newCommand = false;
    return command;
  } else return NULL;
}
