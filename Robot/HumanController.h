#include "Constants.h"

class HumanController {

 public:

  void update();
  int returnSpeedStick();
  int returnTurnStick();
  int returnOperatorStick();
  HumanController(Robot *robotPointer);

 private:
  
  Robot *robot;
  Joystick speedStick;
  Joystick turnStick;
  Joystick operatorStick;

};


