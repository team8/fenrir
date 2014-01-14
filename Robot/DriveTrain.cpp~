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

void DriveTrain::update() {
  /* Command Stuff */
  command = Fenrir.getCommand(); // Don't know how to get Command from Fenrir
  if (command != NULL) {
    if (command.getMethod() == /*Whatever*/) {
      // Do that method
    }
  }
}
void DriveTrain::driveD(double dist){
    
        
}

//sets the spd of all vics to the specified amount b/w 1.0 and -1.0
void DriveTrain::setSpeed(double spd){
    leftFrontVic.set(-spd);
    leftBackVic.set(-spd);
    rightFrontVic.set(spd);
    rightBackVic.set(spd);
    
}
void DriveTrain::rotateA(double angle){
        
        
}
void DriveTrain::rotateS(double speed) {
        
        
}
