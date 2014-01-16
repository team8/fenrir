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
    void rotateA(double angle);
    void rotateS(double rotspd);
    void update();
    void runMethod(Command command);
}
