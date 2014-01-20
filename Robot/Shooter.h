#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState {
  IDLE,  
  LOADED,
  SPINNING_UP,
  AIMING
} ShooterState;

class Shooter {
 
 private:
  
  Victor vic1;
  Victor vic2;
  Victor vic3;
  Victor vic4;
  
  ShooterState state;
 public:
 
  void shoot();
  void update();
  Shooter();
  void runCommand(RobotCommand command);
 
};
