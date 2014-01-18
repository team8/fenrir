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
        //leftEnc.SetDistancePerPulse(not known at the moment);
        //rightEnc.SetDistancePerPulse(not known at the moment);
        leftEnc.Start();
        rightEnc.Start();
        
        // Speed controller stuff
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
	//May use PIDController class
	float m_P = 0.1;
	float m_I = 0.001;
	float m_D = 0.0;
	//float m_tolerance = set something;
	float m_error = dist;
	/*
	while(current error > tolerance){
		calculate value to be written to victors
		DriveTrain::setSpeed(result);
		leftEnc.GetDistance();
		rightEnc.GetDistance();
	}
	if (current error < tolerance){ 
		leftEnc.Reset();
		rightEnc.Reset();
		return;
	}
	*/
	
}

//sets the spd of all vics to the specified amount b/w 1.0 and -1.0
//Makes robot go straight
void DriveTrain::SetSpeed(double spd) {
    leftFrontVic.Set(-spd);
    leftBackVic.Set(-spd);
    rightFrontVic.Set(spd);
    rightBackVic.Set(spd);
}

//lets you rotate in place
void DriveTrain::rotateA(double angle,float turnValue, float speedValue){
	
	bool isAutonomous;
	
	if (isAutonomous == false){ //Teleop mode
		//turns according to the joysticks
	}
	else { //Autonomous mode
		//turns the specified number of degrees
	}
}

//speed < 0 then turns LEFT
//speed > 0 then turns RIGHT
void DriveTrain::rotateS(double speed) {

	leftFrontVic.Set(leftFrontVic.Get()-speed);
	leftBackVic.Set(leftBackVic.Get()-speed);
   	rightFrontVic.Set(rightFrontVic.Get()-speed);
   	rightBackVic.Set(rightBackVic.Get()-speed);

}
