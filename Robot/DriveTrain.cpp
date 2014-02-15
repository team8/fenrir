#include "DriveTrain.h"

DriveTrain::DriveTrain() :		
	// Victors
	leftFrontVic((uint32_t) PORT_DRIVE_VIC_LEFT_FRONT),
	leftBackVic((uint32_t) PORT_DRIVE_VIC_LEFT_BACK),
	rightFrontVic((uint32_t) PORT_DRIVE_VIC_RIGHT_FRONT),
	rightBackVic((uint32_t) PORT_DRIVE_VIC_RIGHT_BACK),

	//gyroscope((uint32_t) PORT_GYRO),

	// Encoders
	leftEnc((uint32_t) 1,(uint32_t) 7, true),
	rightEnc((uint32_t) 12,(uint32_t) 13, true)

	// PIDControllers
	//	leftController(0.1, 0.1, 0.1, &leftEnc, &leftBackVic),
	//rightController(0.1, 0.1, 0.1, &rightEnc, &rightBackVic)
	//angleController(0.1, 0.1, 0.1, &gyroscope, &leftBackVic) 
{
	rotateSpeed=0;
	std::printf("Drive train constructor\n");
	//gyroscope.Start();
	//rightController.SetOutputRange(-1, 1);
    //angleController.SetOutputRange(-1, 1);
}

void DriveTrain::init() {
		rightEnc.Start();
		leftEnc.Start();
		std::printf("Initialized\n");
		rightEnc.SetDistancePerPulse(10.0);
		leftEnc.SetDistancePerPulse(10.0);
		rightEnc.SetPIDSourceParameter(PIDSource::kRate);
		leftEnc.SetPIDSourceParameter(PIDSource::kRate);
		state = STOP_VICTORS;
}

//runs method according to what newCommand is received
void DriveTrain::runCommand(RobotCommand command) {

//	std::printf("Left Distance: %f\n", leftEnc.GetDistance());
//	std::printf("Right Distance: %f\n", rightEnc.GetDistance());
//	std::printf("Left Rate: %f\n", leftEnc.GetRate());
//	std::printf("Right Rate: %f\n", rightEnc.GetRate());
//	std::printf("Left Stopped: %i\n", (int)leftEnc.GetStopped());
//	std::printf("Right Stopped: %i\n", (int)rightEnc.GetStopped());
//	std::printf("Right Get: %d\n", (int)rightEnc.Get());
//	std::printf("Left Get: %d\n", (int)leftEnc.Get());
//	std::printf("Right Raw: %i\n", (int)rightEnc.GetRaw());
//	std::printf("Left Raw: %i\n", (int)leftEnc.GetRaw());

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
	
	switch (state) {

	case ROTATE_SPEED:
		double leftSpeed = min(max(-(targetSpeed + rotateSpeed), -1), 1);
		double rightSpeed = min(max(targetSpeed - rotateSpeed, -1), 1);
//		std::printf("Left Distance: %f\n", rightSpeed);
//		std::printf("Right Distance: %f\n", leftSpeed);
		leftFrontVic.Set(leftSpeed);
		leftBackVic.Set(leftSpeed);
		rightFrontVic.Set(rightSpeed);
		rightBackVic.Set(rightSpeed);
		break;

	case DRIVE_DIST:
		leftFrontVic.Set(leftEnc.PIDGet());
		leftBackVic.Set(leftEnc.PIDGet());
		rightFrontVic.Set(-(rightEnc.PIDGet()));
		rightBackVic.Set(-(rightEnc.PIDGet()));
		break;

	case TURN_ANGLE:
		std::printf("this was commented out what....");
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
	//leftController.SetSetpoint(dist);
	//rightController.SetSetpoint(dist);
	//leftController.Enable();
	//rightController.Enable();
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
