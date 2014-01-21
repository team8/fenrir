#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState {
  STILL,  
  LOADED,
  SPINNING_UP,
  AIMING
} ShooterState;

class Shooter {
 
 private:
  
  Victor shooterVic1;
  Victor shooterVic2;
  Victor shooterVic3;
  Victor shooterVic4;
  
  ShooterState state;
 public:
 
  void shoot();
  void update();
  Shooter();
  void runCommand(RobotCommand command);
 
};
