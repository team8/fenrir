#include "HumanController.h"

HumanController::HumanController(Robot *robotPointer)

  //

  operatorStick(PORT_OPERATOR);
  turnStick(PORT_TURN);
  speedStick(PORT_SPEED);
  
{  
  this-> robot = robotPointer;
}

/* Command example
   void * argPointer = malloc(sizeof(DriveArgs));
  argPointer -> value = Enter any number here;
  robot.setCommand(Command command(false, DRIVE, Method, argPointer)); // Replace Method with the method. First value must be false
*/

HumanController::update() {
    //Joystick.GetY() returns value b/w -1 and 1
    
    //takes the input from the joysticks 
    float speed = speedStick.GetY(); 
    float turn = turnStick.GetX(); 
    float input = speed - turn;
    
    //here call the appropriate function from drive train
}

HumanController::getSpeedStick() {
      float speed = speedStick.GetY(); 
      return speed;
}


HumanController::getTurnStick() {
    float turn = turnStick.GetX();
      
    void * argPointer = malloc(sizeof(DriveArgs));
    argPointer -> value = /*Enter parameter here*/;
    robot.setCommand(Command command(false, DRIVE, /*Enter method here*/, argPointer));
      
    return turn;
}


HumanController::getOperatorStick() {
    //find what the operator stick actually does :D
  
}  
