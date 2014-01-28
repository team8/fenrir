#ifndef AUTONOMOUSCONTROLLER_H
#define	AUTONOMOUSCONTROLLER_H
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"
#include <WPILib.h>

class AutonomousController {

 public:
  AutonomousController(Robot* robotPointer);
  void update();
  void startTimer();
  void rotateDegrees();

 private:
 
  Timer time; 
  Robot* robot;
  void drive();
  void stop();
  bool shoot();
  Ultrasonic ultraLeft(ECHO_PULSE_OUT_1, TRIGGER_PULSE_IN_1);
  Ultrasonic ultraRight(ECHO_PULSE_OUT_2, TRIGGER_PULSE_IN_2);
  bool targetReached;
};
#endif
