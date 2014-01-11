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
        
}
