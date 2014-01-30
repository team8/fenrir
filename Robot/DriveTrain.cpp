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
        leftEnc((uint32_t)PORT_ENCODER_LEFT_A, (uint32_t)PORT_ENCODER_LEFT_B, true, k4X), 
        rightEnc((uint32_t)PORT_ENCODER_RIGHT_A, (uint32_t)PORT_ENCODER_RIGHT_B, true, k4X), 
        //leftEnc.SetPIDSourceParameter(kdistance),
		//rightEnc.SetPIDSourceParameter(kdistance),
        
        // PIDControllers
		leftController(0.1, 0.1, 0.1, &leftEnc, &leftBackVic),
		rightController(0.1,0.1, 0.1, &rightEnc, &rightBackVic),
		angleController(0.1, 0.1, 0.1, &gyroscope, &leftBackVic)
{
    //leftEnc.SetDistancePerPulse(not known at the moment);
    //rightEnc.SetDistancePerPulse(not known at the moment);
    leftEnc.Start();
    rightEnc.Start();
    rightController.SetOutputRange(-1,1);
    leftController.SetOutputRange(-1,1);
    angleController.SetOutputRange(-1, 1);
}

//runs method according to what newCommand is received
void DriveTrain::runCommand(RobotCommand command) {
    
	DriveArgs* args = (DriveArgs*) command.argPointer;
    switch (command.getMethod().driveMethod) {
    case RobotCommand::SETSPEED:
      setSpeed(args -> speedValue);
      break;
    case RobotCommand::DRIVEDIST:
      driveD(args -> driveDist);
      break;
    case RobotCommand::ROTATEANGLE:
      rotateA(args -> rotAngle);
      break;
    case RobotCommand::ROTATESPEED:
      rotateS(args -> rotSpeed);
      break;
    case RobotCommand::STOPVICTORS:
      stopVictors();
      break;
    }
    free(args);
}

void DriveTrain::update() {
	
	switch(state){
	
		case ROTATE_SPEED:
			leftFrontVic.Set(min(max(-(targetSpeed+rotateSpeed),-1),1));
			leftBackVic.Set(min(max(-(targetSpeed+rotateSpeed),-1),1));
			rightFrontVic.Set(min(max(targetSpeed-rotateSpeed,-1),1));
			rightBackVic.Set(min(max(targetSpeed-rotateSpeed,-1),1));
			break;
		case DRIVE_DIST:
			leftFrontVic.Set(-(leftController.Get()));
			leftBackVic.Set(-(leftController.Get()));
			rightFrontVic.Set(rightController.Get());
			rightBackVic.Set(rightController.Get());
			break;
		case TURN_ANGLE:
			leftFrontVic.Set(-(angleController.Get()));
			leftBackVic.Set(-(angleController.Get()));
			rightFrontVic.Set(angleController.Get());
			rightBackVic.Set(angleController.Get());
			break;
		case STOP_VICTORS:
			leftFrontVic.Set(0);
			leftBackVic.Set(0);
			rightFrontVic.Set(0);
			rightBackVic.Set(0);
			
			break;
	}
}
//Drives robot certain distance
//Will use PID to determine output for victors
//Uses encoders
void DriveTrain::driveD(float dist) {
	
	state = DRIVE_DIST;
	leftEnc.Reset();
	rightEnc.Reset();
	leftController.SetSetpoint(dist);
	rightController.SetSetpoint(dist);
	leftController.Enable();
	rightController.Enable();

}

//sets the spd of all vics to the specified amount b/w 1.0 and -1.0
//Makes robot go straight
void DriveTrain::setSpeed(double spd) {
	
	state = ROTATE_SPEED;
	targetSpeed = spd;

}

//lets you rotate in place
void DriveTrain::rotateA(double angle){
	
	state = TURN_ANGLE;
	gyroscope.Reset();
	
	angleController.SetSetpoint(angle);
	angleController.Enable();
	
	rotateAngle = angle;
	
}
//Sets speed of rotation
//speed < 0 then turns LEFT
//speed > 0 then turns RIGHT
void DriveTrain::rotateS(double speed) {
	
	rotateSpeed = speed;
	state = ROTATE_SPEED;

}

void DriveTrain::stopVictors(){
	state = ROTATE_SPEED; 

}
