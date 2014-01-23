#ifndef HUMANCONTROLLER_H
#define HUMANCONTROLLER_H
#include "Constants.h"

#include "Robot.h"
#include "RobotCommand.h"
#include <WPILib.h>

class HumanController {

 public:
  void update();
  float getSpeedStick();
  float getTurnStick();
  float getAccumulatorStick();
  bool getAccumulatorButton();
  bool getShootButton();
  HumanController(Robot *robotPointer);

 private:
  Robot *robot;
  Joystick speedStick;
  Joystick turnStick;
  Joystick operatorStick;
  bool buttonPrev;
};
#endif