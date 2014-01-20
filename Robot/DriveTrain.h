#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Constants.h"
#include <WPILib.h>
#include "RobotCommand.h"

typedef enum {
	
	DRIVE_DIST,
	TELEOP,
	TURN_ANGLE
	
	
}driveState;

class DriveTrain {
    private:
    
    // Victors 
    Victor leftFrontVic;
    Victor leftBackVic;
    Victor rightFrontVic;
    Victor rightBackVic;
    Gyro gyroscope;
    
    // Encoders
    Encoder leftEnc;
    Encoder rightEnc;

    //PID Controllers
    PIDController leftController;
    PIDController rightController;
    
    //target speeds 
    
    double targetSpeed;
    double rotateSpeed;
    double rotateAngle;
    
    //state 
    
    driveState state;
    
    
    public:
    
    DriveTrain();
    //Takes input of distance to destination
    //Will use PID or PIDControllers to calculate input for victors. 
    //Uses encoders as input for distance from destination
    void driveD(float dist);
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
    void stopRotate(double speed);
    void update();
    void runMethod(RobotCommand newCommand);
};
#endif
