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
    //takes a speed between 1 through -1 as a parameter and sets all victors to this speed, this will set it to go
    //straight only because all the victors are at the same speed
    void setSpeed(double spd);
    //this is a work in progress, right now, it doesn't do anything, what we want it to do is call rotateS and rotate 
    //until the target angle has been reached. 
    //I'm not sure if there is going to be a default speed for this rotate thing. :P
    void rotateA(double angle);
    //takes current speed, and subtracts speed one one side and increases on another. -1 is left 1 is right.
    //can someone check the logic to this? thanks
    void rotateS(double speed);
    void update();
    void runMethod(Command newCommand);
}
