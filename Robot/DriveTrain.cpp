#include "Constants.h"
#include "DriveTrain.h"

DriveTrain::DriveTrain() :

        // Victors
        leftFrontVic(PORT_DRIVE_VIC_1),
        leftBackVic(PORT_DRIVE_VIC_2),
        rightFrontVic(PORT_DRIVE_VIC_3),
        rightBackVic(PORT_DRIVE_VIC_4),
        gyroscope((uint32_t)PORT_GYRO),
        
        // Encoders
        leftEnc((uint32_t)PORT_ENCODER_LEFT_A, (uint32_t)PORT_ENCODER_LEFT_B), 
        rightEnc((uint32_t)PORT_ENCODER_RIGHT_A, (uint32_t)PORT_ENCODER_RIGHT_B), 
        
        // Speed controller stuff
		controller(0.1, 0.1, 0.1, &leftEnc, &leftBackVic)
{
    //leftEnc.SetDistancePerPulse(not known at the moment);
    //rightEnc.SetDistancePerPulse(not known at the moment);
    leftEnc.Start();
    rightEnc.Start();
    controller.SetOutputRange(-1,1);
}

//runs method according to what newCommand is recbeived
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
void DriveTrain::driveD(float dist) {
	
	leftEnc.Reset();
	rightEnc.Reset();
	controller.SetSetpoint(dist);
	controller.Enable();
	while(controller.GetError()>.5){
    	leftFrontVic.Set(controller.Get());
    	leftBackVic.Set(controller.Get());
    	rightFrontVic.Set(controller.Get());
    	rightBackVic.Set(controller.Get());
	}
		leftFrontVic.Set(0);
		leftBackVic.Set(0);
		rightFrontVic.Set(0);
		rightBackVic.Set(0);
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
	gyroscope.Reset();
	if(gyroscope.GetAngle()!=angle){
		rotateS(DEFAULT_AUTO_ROTATE);
	}
	if(gyroscope.GetAngle()==angle){
		stopRotate(DEFAULT_AUTO_ROTATE);
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

void DriveTrain::stopRotate(double speed){
	
	leftFrontVic.Set(leftFrontVic.Get()+speed);
	leftBackVic.Set(leftBackVic.Get()+speed);
   	rightFrontVic.Set(rightFrontVic.Get()+speed);
   	rightBackVic.Set(rightBackVic.Get()+speed);
	
}
