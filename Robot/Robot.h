#include <WIPLib.h>
#include "Constants.h"
#include "AutonomousController.h"
#include "DriveTrain.h"
#include "HumanController.h"


class Robot {
    
    private:
    
      DriveTrain driveTrain;
      
    
    public:
    
    void setSpeed(float s);
    void rotateSpeed(float s);
    void setCommand(Command newCommand);
    
}
