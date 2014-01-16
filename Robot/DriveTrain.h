#include "Constants.h"
#include <WPILib.h>
#include "Command.h"

class DriveTrain {
    private:
    
    // Victors
    Victor leftFrontVic;
    Victor leftBackVic;
    Victor rightFrontVic;
    Victor rightBackVic;
    
    // Encoders
    Encoder leftEnc;
    Encoder rightEnc;
    
    Command command;
    
    // Needs speed controller stuff
    
    public:
    
    DriveTrain();
    void driveD(double dist);
    void setSpeed(double spd);
    void rotate(double angle);
    void update();
    void runMethod(Command newCommand);
}
