#ifndef ROBOT_H
#define ROBOT_H
#include <WPILib.h>
#include "Constants.h"
#include "DriveTrain.h"
#include "Shooter.h"
#include "RobotCommand.h"


class Robot {
    
    private:
    
      DriveTrain driveTrain;
      Shooter shooter;
    
    public:
    Robot();
 //   void setSpeed(float s);
   // void rotateSpeed(float s);
    void setCommand(RobotCommand newCommand);
    
};
#endif
