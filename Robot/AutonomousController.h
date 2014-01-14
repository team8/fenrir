#include "Constants.h"

class AutonomousController {

 public:

  AutonomousController(Robot *robotPointer);
  void update();
  void startTimer();

 private:
 
  Timer time; 
  Robot *robot;
  void drive();
  void stop();
  bool shoot();
  Command getCommand();
  
  bool targetReached;
  Command command;
  bool newCommand = false;
};
