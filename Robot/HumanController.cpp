#include "HumanController.h"
/* Command example - How to issue commands
  void * argPointer = malloc(sizeof(DriveArgs)); //this lets you access the drive args stored in command
  argPointer -> variable in DriveArgs = Enter parameter here; //this lets you set a variable to what you want
  robot.setCommand(Command command(false, DRIVE, Method, argPointer)); //replace Method with appropriate method
*/

HumanController::HumanController(Robot *robotPointer)
  operatorStick(PORT_OPERATOR);
  turnStick(PORT_TURN);
  speedStick(PORT_SPEED);
{  
  this-> robot = robotPointer;
}



//This is the part that loops repeatedly, issuing commands
HumanController::update() {
    
    //Here call the appropriate function from drive train
    
    void * argPointer = malloc(sizeof(DriveArgs));
    
    argPointer -> speedValue = HumanController.getSpeedStick();
    argPointer -> turnValue = HumanController.getTurnStick();
    robot.setCommand(Command command(false, DRIVE, /*Enter method here*/, argPointer));
    
}

HumanController::getSpeedStick() {
      float speed = speedStick.GetY(); 
      return speed;
}


HumanController::getTurnStick() {
    float turn = turnStick.GetX();
    return turn;
}


HumanController::getOperatorStick() {
    //find what the operator stick actually does :D
  
}  
