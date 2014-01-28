#ifndef AUTONOMOUSCONTROLLER_H
#define	AUTONOMOUSCONTROLLER_H
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"

class AutonomousController {

 public:
  AutonomousController(Robot* robotPointer);
  void update();
  void startTimer();
  double rotateDegrees();

 private:
 
  Timer time; 
  Robot* robot;
  void drive();
  void stop();
  bool shoot();
  
  bool targetReached;
};
#endif
