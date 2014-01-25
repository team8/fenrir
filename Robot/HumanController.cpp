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
    Method setSpeed;
    setSpeed.driveMethod=SETSPEED;
    RobotCommand command(DRIVE,setSpeed, argPointer);
    robot -> setCommand(command);
    if(accuButtonPrev!=getAccumulatorButton()){
    	if(getAccumulatorButton()){
    		Method setAccumulator;
    		setAccumulator.accumulatorMethod=ACCUMULATE;
    		RobotCommand command(ACCUMULATOR, setAccumulator, 0);
    		robot -> setCommand(command);
    	}
    	else{
    		Method stopAccumulator;
    		stopAccumulator.accumulatorMethod=STOP;
    		RobotCommand command(ACCUMULATOR, stopAccumulator, 0);
    		robot -> setCommand(command);
    	}
    }
    
    if(shootButtonPrev!=getShootButton()){
    	if(getShootButton()){
    		Method shoot;
    		shoot.shooterMethod = SHOOT;
    		RobotCommand command(SHOOTER, shoot, 0);
    		robot -> setCommand(command);
    	}
    }
    accuButtonPrev=getAccumulatorButton();
    shootButtonPrev=getShootButton();
}

float HumanController::getSpeedStick(){
      float speed = speedStick.GetY(); 
      return speed;
}

float HumanController::getTurnStick() {
    float turn = turnStick.GetX();
    return turn;
}

float HumanController::getAccumulatorStick() {
	return operatorStick.GetY(); // For adjusting the accumulator with Operator stick
}

bool HumanController::getAccumulatorButton() {
    return operatorStick.GetRawButton((uint32_t)ACCUMULATOR_BUTTON_PORT); // Get button to start accumulator from Operator stick
}

bool HumanController::getShootButton() {
    return operatorStick.GetTrigger(); // Get trigger button to shoot from Operator stick
}

bool HumanController::getWarmupButton() {
    return operatorStick.GetRawButton((uint32_t)WARMUP_BUTTON_PORT); // Get button to start shooter warmup from Operator stick
}

bool HumanControlloer::getPassButton() {
	return operatorStick.GetRawButton((unint32_t)PASS_BUTTON_PORT);
}
