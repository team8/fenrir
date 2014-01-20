#include "HumanController.h"
/* Command example - How to issue commands
  void * argPointer = malloc(sizeof(DriveArgs)); //this lets you access the drive args stored in command
  argPointer -> variable in DriveArgs = Enter parameter here; //this lets you set a variable to what you want
  robot.setCommand(Command command(false, DRIVE, Method, argPointer)); //replace Method with appropriate method
*/

HumanController::HumanController(Robot *robotPointer):

	speedStick(PORT_SPEED),
	turnStick(PORT_TURN),
	operatorStick(PORT_OPERATOR)


{  
  this-> robot = robotPointer;
} 



//This is the part that loops repeatedly, issuing commands
void HumanController::update(){
    
    //Here call the appropriate function from drive train
    
    void * argPointer = malloc(sizeof(DriveArgs));
    
    ((DriveArgs*)argPointer) -> speedValue = speedStick.GetY();
    ((DriveArgs*)argPointer) -> turnValue = turnStick.GetX();
    RobotCommand command(false, DRIVE, SETSPEED, argPointer);
    robot -> setCommand(command);
    if(buttonPrev!=operatorStick.GetTrigger()){
    	if(operatorStick.GetTrigger()==true){
    		RobotCommand command(true, ACCUMULATOR, ACCUMULATE, 0);
    	}
    	else if(operatorStick.GetTrigger()==false){
    		RobotCommand command(false, ACCUMULATOR, STOP, 0);
    	}
    }
    buttonPrev=operatorStick.GetTrigger();
}

float HumanController::getSpeedStick(){
      float speed = speedStick.GetY(); 
      return speed;
}


float HumanController::getTurnStick() {
    float turn = turnStick.GetX();
    return turn;
}


float HumanController::getOperatorStick() {
    //find what the operator stick actually does :D
	float something = 0.0;
	return something;
}  
