#include "HumanController.h"

HumanController::HumanController(Robot *robotPointer)

  //

  operatorStick(PORT_OPERATOR);
  turnStick(PORT_TURN);
  speedStick(PORT_SPEED);
  
{  
  this-> robot = robotPointer;
}

HumanController::update() {
    //Joystick.GetY() returns value b/w -1 and 1
    
    //takes the input from the joysticks 
    float speed = speedStick.GetY(); 
    float turn = turnStick.GetX(); 
    float input = speed - turn;
    
    //here call the appropriate function from drive train
}

HumanController::returnSpeedStick() {
  
      float speed = speedStick.GetY(); 
      return speed;
  
}

HumanController::returnTurnStick() {
      float turn = turnStick.GetX(); 
      return turn
  
}
HumanController::returnOperatorStick() {
    //find what the operator stick actually does :D
  
}  
