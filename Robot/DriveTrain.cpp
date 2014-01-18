#include "Constants.h"
#include "DriveTrain.h"

DriveTrain::DriveTrain() :

        // Victors
        leftFrontVic(PORT_DRIVE_VIC_1),
        leftBackVic(PORT_DRIVE_VIC_2),
        rightFrontVic(PORT_DRIVE_VIC_3),
        rightBackVic(PORT_DRIVE_VIC_4),
        
        // Encoders
        leftEnc((uint32_t)PORT_ENCODER_LEFT_A, (uint32_t)PORT_ENCODER_LEFT_B), 
        rightEnc((uint32_t)PORT_ENCODER_RIGHT_A, (uint32_t)PORT_ENCODER_RIGHT_B), 
        
        // Speed controller stuff
		encCntrlr(0.1, 0.1, 0.1, &leftEnc, &leftBackVic)
{
    //leftEnc.SetDistancePerPulse(not known at the moment);
    //rightEnc.SetDistancePerPulse(not known at the moment);
    leftEnc.Start();
    rightEnc.Start();
}

//runs method according to what newCommand is received
void DriveTrain::runMethod(RobotCommand newCommand) {
        DriveArgs* args = (DriveArgs*) newCommand.argPointer;
        if (newCommand.getMethod() == SETSPEED) {
                setSpeed(args -> driveSpeed);
        }
        else if (newCommand.getMethod() == DRIVEDIST) {
                driveD(args -> driveDist);
        }
        else if (newCommand.getMethod() == ROTATEANGLE) {
                rotateA(args -> rotAngle);
        }
        free(args);
}

void DriveTrain::update() {
  
}
//Drives robot certain distance
//Will use PID to determine output for victors
//Uses encoders
void DriveTrain::driveD(double dist) {
	
	//to be changed
	//May use PIDController class
	float m_P = 0.1;
	float m_I = 0.001;
	float m_D = 0.0;
	//float m_tolerance = set something;
	float m_error = dist;
	leftEnc.SetPIDSourceParameter(PIDSource::kDistance);
	rightEnc.SetPIDSourceParameter(PIDSource::kDistance);
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
void DriveTrain::setSpeed(double spd) {
    leftFrontVic.Set(-spd);
    leftBackVic.Set(-spd);
    rightFrontVic.Set(spd);
    rightBackVic.Set(spd);
}

//lets you rotate in place
void DriveTrain::rotateA(double angle){
	
	bool isAutonomous;
	
	if (isAutonomous == false){ //Teleop mode
		//turns according to the joysticks
	}
	else { //Autonomous mode
		//turns the specified number of degrees
	}
}
//Sets speed of rotation
//speed < 0 then turns LEFT
//speed > 0 then turns RIGHT
void DriveTrain::rotateS(double speed) {

	leftFrontVic.Set(leftFrontVic.Get()-speed);
	leftBackVic.Set(leftBackVic.Get()-speed);
   	rightFrontVic.Set(rightFrontVic.Get()-speed);
   	rightBackVic.Set(rightBackVic.Get()-speed);

}
