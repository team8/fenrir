#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Constants.h"
#include <WPILib.h>
#include "RobotCommand.h"

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
    
    PIDController encCntrlr;
<<<<<<< HEAD
    Command command;
    
=======
	
    Command command;
    
    
    
>>>>>>> 5149425dadcfc59572c9a34b5dab8aafd2c289a0
    // Needs speed controller stuff
    
    public:
    
    DriveTrain();
    //Takes input of distance to destination
    //Will use PID or PIDControllers to calculate input for victors. 
    //Uses encoders as input for distance from destination
    void driveD(double dist);
    //Takes input of -1 to 1 and sets speed of victors. 
    //Only drives straight
    void setSpeed(double spd);
    //this is a work in progress, right now, it doesn't do anything, what we want it to do is call rotateS and rotate 
    //until the target angle has been reached. 
    //I'm not sure if there is going to be a default speed for this rotate thing. :P
    void rotateA(double angle);
    //takes current speed, and subtracts speed one one side and increases on another. -1 is left 1 is right.
    //can someone check the logic to this? thanks
    void rotateS(double speed);
    void update();
    void runMethod(RobotCommand newCommand);
};
#endif
