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

//runs method according to what newCommand is received
void DriveTrain::runMethod(Command newCommand) {
	command = newCommand;
        DriveArgs * args = (DriveArgs*) newCommand.argPointer;
        if (newCommand.getMethod() == SETSPEED) {
                setSpeed(newCommand.args -> value);
        } else if (newCommand.getMethod() == DRIVEDIST) {
                direvD(newCommand.args -> value);
        } else if (newCommand.getMethod() == ROTATEANGLE) {
                rotateA(newCommand.args -> value);
        } else if (newCommand.getMethod() == ROTATESPEED) {
                rotateS(newCommand.args -> value);
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

//lets you rotate in place
void DriveTrain::rotate(double angle){
	bool mode =Command.getParent(); //true if call is from autonomous, false if command is from teleop
	if(mode==false){
		//turns the specified number of degrees
	}
	else {
		//turns according to the joysticks
	}
}
