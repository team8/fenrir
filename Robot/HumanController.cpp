#include "HumanController.h"

HumanController::HumanController(Robot *robotPointer)

  //

  operatorStick(PORT_OPERATOR);
  turnStick(PORT_TURN);
  speedStick(PORT_SPEED);
  
{  
  this-> robot = robotPointer;
  
}

HumanController:TeleopPeriodic() {
    //Joystick.GetY() returns value b/w -1 and 1
    
    //takes the input from the joysticks and multiplies it by a constant (1.0)
    float speed = 1.0 * speedStick.GetY(); 
    float turn = 1.0 * turnStick.GetX(); 
    float input = speed - turn;
    
    leftFrontVic.Set(-input);
    leftBackVic.Set(-input);
    rightFrontVic.Set(input);
    rightBackVic.Set(input); 

}


}
