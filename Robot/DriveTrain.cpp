#include "DriveTrain.h"

DriveTrain::DriveTrain() :

        // Victors
        leftFrontVic(PORT_DRIVE_VIC_1),
        leftBackVic(PORT_DRIVE_VIC_2),
        rightFrontVic(PORT_DRIVE_VIC_3),
        rightBackVic(PORT_DRIVE_VIC_4),
        
        // Encoders
        leftEnc(PORT_ENCODER_RIGHT), 
        rightEnc(PORT_ENCODER_LEFT) 
        
        // Needs speed controller stuff
{
        
}

void DriveTrain::runMethod(Command command) {
        DriveArgs * args = (DriveArgs*) command.argPointer;
        if (command.getMethod() == SETSPEED) {
                setSpeed(command.args -> value);
        } else if (command.getMethod() == DRIVEDIST) {
                direvD(command.args -> value);
        } else if (command.getMethod() == ROTATEANGLE) {
                rotateA(command.args -> value);
        } else if (command.getMethod() == ROTATESPEED) {
                rotateS(command.args -> value);
        }
        free(args);
}

void DriveTrain::update() {
  
}
void DriveTrain::driveD(double dist){
    
        
}

//sets the spd of all vics to the specified amount b/w 1.0 and -1.0
//this method only makes the robot go staight, sorry guys.
void DriveTrain::setSpeed(double spd){
    leftFrontVic.set(-spd);
    leftBackVic.set(-spd);
    rightFrontVic.set(spd);
    rightBackVic.set(spd);
    
}
void DriveTrain::rotateA(double angle){
    
    //temporary old code, may or may not use
    leftFrontVic.Set(-input);
    leftBackVic.Set(-input);
    rightFrontVic.Set(input);
    rightBackVic.Set(input); 
        
}
void DriveTrain::rotateS(double speed) {
        
        
}
