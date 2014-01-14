#include "Constants.h"

class HumanController {

 public:

  void update();
  HumanController(Robot *robotPointer);
  Command getCommand();

 private:
  
  Robot *robot;
  Joystick speedStick;
  Joystick turnStick;
  Joystick operatorStick;

  Command command;
  bool newCommand;
};


