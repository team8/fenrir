#include <WIPLib.h>
#include "Constants.h"
#include "AutonomousController.h"
#include "DriveTrain.h"
#include "HumanController.h"


class Robot {
    
    private:
    
      DriveTrain driveTrain;
      Command command;
      
    
    public:
    
    void setSpeed(float s);
    void rotateSpeed(float s);
    void setCommand(Command newCommand);
    
}
