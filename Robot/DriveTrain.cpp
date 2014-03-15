#include "DriveTrain.h"

DriveTrain::DriveTrain() :
// Victors
leftFrontVic((uint32_t) PORT_DRIVE_VIC_LEFT_FRONT),
leftBackVic((uint32_t) PORT_DRIVE_VIC_LEFT_BACK),
rightFrontVic((uint32_t) PORT_DRIVE_VIC_RIGHT_FRONT),
rightBackVic((uint32_t) PORT_DRIVE_VIC_RIGHT_BACK),

//gyroscope((uint32_t) PORT_GYRO),

// Encoders
leftEnc((uint32_t) PORT_ENCODER_LEFT_A,
		(uint32_t) PORT_ENCODER_LEFT_B, false),
rightEnc((uint32_t) PORT_ENCODER_RIGHT_A,
		(uint32_t) PORT_ENCODER_RIGHT_B, true),

// PIDControllers
leftBackController(0.1, 0.01, 0.1, &leftEnc, &leftBackVic),
rightBackController(0.1, 0.01, 0.1, &rightEnc, &rightBackVic),
leftFrontController(0.1, 0.01, 0.1, &leftEnc, &leftFrontVic),
rightFrontController(0.1, 0.01, 0.1, &rightEnc, &rightFrontVic)
//angleController(0.1, 0.1, 0.1, &gyroscope, &leftBackVic)

{
	rotateSpeed = 0;
	std::printf("Drive train constructor\n");
	//gyroscope.Start();
//	rightController.SetOutputRange(-1, 1);
	//angleController.SetOutputRange(-1, 1);
}

void DriveTrain::init() {
	rightEnc.Reset();
	leftEnc.Reset();
	rightEnc.Start();
	leftEnc.Start();
	//circumference = 19 inches
	rightFrontController.SetOutputRange(-1, 1);
	leftFrontController.SetOutputRange(-1, 1);
	rightBackController.SetOutputRange(-1, 1);
	leftBackController.SetOutputRange(-1, 1);
	rightEnc.SetDistancePerPulse(.0782);//(.07734);
	leftEnc.SetDistancePerPulse(.0813);//(.07849);
	rightEnc.SetPIDSourceParameter(PIDSource::kDistance);
	leftEnc.SetPIDSourceParameter(PIDSource::kDistance);
	state = STOP_VICTORS;
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
	
	//std::printf("Left Enc: %f\n",leftEnc.GetDistance()); 
	//std::printf("Right Enc: %f\n",rightEnc.GetDistance());
	
	switch (state) {

	case ROTATE_SPEED:
		double leftSpeed = min(max(-(targetSpeed + rotateSpeed), -1), 1);
		double rightSpeed = min(max(targetSpeed - rotateSpeed, -1), 1);
		leftFrontVic.Set(leftSpeed);
		leftBackVic.Set(leftSpeed);
		rightFrontVic.Set(rightSpeed);
		rightBackVic.Set(rightSpeed);
		break;

	case DRIVE_DIST:
	//	double average = (rightEnc.GetDistance()+leftEnc.GetDistance())/2;
//		if(rightEnc.GetDistance() < abs(targetDist)){
//			std::printf("getting called right");
//			rightFrontVic.Set(0.3);
//			rightBackVic.Set(0.3);
//		}
//		if(leftEnc.GetDistance() < abs(targetDist)){
//			std::printf("getting called left");
//			leftFrontVic.Set(-0.3);
//			leftBackVic.Set(-0.3);
//		}

	break;

	case TURN_ANGLE:
		//		leftFrontVic.Set(-(angleController.Get()));
		//		leftBackVic.Set(-(angleController.Get()));
		//		rightFrontVic.Set(angleController.Get());
		//		rightBackVic.Set(angleController.Get());
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
void DriveTrain::driveD(double dist) {
	leftEnc.Reset();
	rightEnc.Reset();
	leftFrontController.SetSetpoint(dist);
	rightFrontController.SetSetpoint(dist);
	leftBackController.SetSetpoint(dist);
	rightBackController.SetSetpoint(dist);
	leftFrontController.Enable();
	rightFrontController.Enable();
	leftBackController.Enable();
	rightBackController.Enable();
	targetDist = dist; 
	state = DRIVE_DIST;
}

//sets the spd of all vics to the specified amount between 1.0 and -1.0
//Makes robot go straight
void DriveTrain::setSpeed(double spd) {
	targetSpeed = spd;
	state = ROTATE_SPEED;
}

//lets you rotate in place
void DriveTrain::rotateA(double angle) {
	//	gyroscope.Reset();
	//	angleController.SetSetpoint(angle);
	//	angleController.Enable();
	//	rotateAngle = angle;
	state = TURN_ANGLE;
}

//Sets speed of rotation
//speed < 0 then turns LEFT
//speed > 0 then turns RIGHT
void DriveTrain::rotateS(double speed) {
	rotateSpeed = speed;
	state = ROTATE_SPEED;
}

void DriveTrain::stopVictors() {
	state = STOP_VICTORS;
}

double DriveTrain::getRightEnc() {
	return rightEnc.GetDistance();
}

double DriveTrain::getLeftEnc() {
	return leftEnc.GetDistance();
}

