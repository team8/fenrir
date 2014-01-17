#include "DriveTrain.h"

DriveTrain::DriveTrain() :

        // Victors
        leftFrontVic(PORT_DRIVE_VIC_1),
        leftBackVic(PORT_DRIVE_VIC_2),
        rightFrontVic(PORT_DRIVE_VIC_3),
        rightBackVic(PORT_DRIVE_VIC_4),
        
        // Encoders
        leftEnc(PORT_ENCODER_LEFT), 
        rightEnc(PORT_ENCODER_RIGHT) 
        
        // Needs speed controller stuff
{
        
}

//runs method according to what newCommand is received
void DriveTrain::runMethod(Command newCommand) {
        DriveArgs* args = (DriveArgs*) newCommand.argPointer;
        if (command.getMethod() == SETSPEED) {
                setSpeed(args -> driveSpeed);
        }
        else if (command.getMethod() == DRIVEDIST) {
                driveD(args -> driveDist);
        }
        else if (command.getMethod() == ROTATEANGLE) {
                rotateA(args -> rotAngle);
        }
        free(args);
}

void DriveTrain::update() {
  
}
void DriveTrain::driveD(double dist) {
	//to be changed
	float m_P = 0.1;
	float m_I = 0.001;
	float m_D = 0.0;
	//float m_tolerance = set something;
	float m_error = dist;
	/*
	while(current error > tolerance){
		calculate value to be written to victors
		set victors
	}
	if (current error < tolerance){ return;}
	*/
	
}

//sets the spd of all vics to the specified amount b/w 1.0 and -1.0
//this method only makes the robot go staight, sorry guys.
void DriveTrain::setSpeed(double spd) {
    leftFrontVic.set(-spd);
    leftBackVic.set(-spd);
    rightFrontVic.set(spd);
    rightBackVic.set(spd);
}

//lets you rotate in place
void DriveTrain::rotateA(double angle){
	
	bool isAutonomous = Command.getParent(); //true if call is from autonomous, false if command is from teleop

	if (isAutonomous == false){
		//turns according to the joysticks
	}
	else {
		//turns the specified number of degrees
	}
}

//speed < 0 then turns LEFT
//speed > 0 then turns RIGHT
void DriveTrain::rotate(double speed) {
	if (speed > 0) {
		leftFrontVic.set(leftFrontVic.get()-speed);
	   	leftBackVic.set(leftBackVic.get()-speed);
   		rightFrontVic.set(rightFrontVic.get()-speed);
   		rightBackVic.set(rightBackVic.get()-speed);
	}    	
	if (speed < 0) { 
		leftFrontVic.set(leftFrontVic.get()+speed);
    	leftBackVic.set(leftBackVic.get()+speed);
    	rightFrontVic.set(rightFrontVic.get()+speed);
    	rightBackVic.set(rightBackVic.get()+speed);
	}    	
}
