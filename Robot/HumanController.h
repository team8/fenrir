#ifndef HUMANCONTROLLER_H
#define HUMANCONTROLLER_H
#include "Constants.h"

class HumanController {

 public:

  void update();
  float returnSpeedStick();
  float returnTurnStick();
  float returnOperatorStick();
  HumanController(Robot *robotPointer);

 private:
  
  Robot *robot;
  Joystick speedStick;
  Joystick turnStick;
  Joystick operatorStick;

};
#endif

