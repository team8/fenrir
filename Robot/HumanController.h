#ifndef HUMANCONTROLLER_H
#define HUMANCONTROLLER_H
#include "Constants.h"

#include "Robot.h"
#include <WPILib.h>

class HumanController {

 public:

  void update();
  float getSpeedStick();
  float getTurnStick();
  float getOperatorStick();
  HumanController(Robot *robotPointer);

 private:
  
  Robot *robot;
  Joystick speedStick;
  Joystick turnStick;
  Joystick operatorStick;


};
#endif

