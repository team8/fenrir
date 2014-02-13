#include "DriveTrain.h"

DriveTrain::DriveTrain() :		
	// Victors
	leftFrontVic((uint32_t) PORT_DRIVE_VIC_1),
	leftBackVic((uint32_t) PORT_DRIVE_VIC_2),
	rightFrontVic((uint32_t) PORT_DRIVE_VIC_3),
	rightBackVic((uint32_t) PORT_DRIVE_VIC_4),

//	gyroscope((uint32_t) PORT_GYRO),

	// Encoders
	leftEnc((uint32_t) 0,(uint32_t) 0, true),
	rightEnc((uint32_t) 0,(uint32_t) 0, true)

	// PIDControllers
//	leftController(0.1, 0.1, 0.1, &leftEnc, &leftBackVic),
	//rightController(0.1, 0.1, 0.1, &rightEnc, &rightBackVic)
	//angleController(0.1, 0.1, 0.1, &gyroscope, &leftBackVic) 
{
	std::printf("Drive train constructor\n");
	//gyroscope.Start();
	//rightController.SetOutputRange(-1, 1);
    //angleController.SetOutputRange(-1, 1);
}

void DriveTrain::init() {
		rightEnc.Start();
		leftEnc.Start();
		std::printf("Initialized\n");
		rightEnc.SetDistancePerPulse(1.0);
		leftEnc.SetDistancePerPulse(1.0);
		rightEnc.SetPIDSourceParameter(PIDSource::kDistance);
		leftEnc.SetPIDSourceParameter(PIDSource::kDistance);
		state = STOP_VICTORS;
}

//runs method according to what newCommand is received
void DriveTrain::runCommand(RobotCommand command) {

	DriveArgs* args = (DriveArgs*) command.argPointer;
	switch (command.getMethod().driveMethod) {
	case RobotCommand::SETSPEED:
		std::printf("setspeed\n");
		setSpeed(args -> speedValue);
		break;
	case RobotCommand::DRIVEDIST:
		std::printf("driveDist\n");
		driveD(args -> driveDist);
		break;
	case RobotCommand::ROTATEANGLE:
		std::printf("rotateangle\n");
		rotateA(args -> rotAngle);
		break;
	case RobotCommand::ROTATESPEED:
		std::printf("rotatespeed\n");
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
		double rightSpeed = min(max(-(targetSpeed + rotateSpeed), -1), 1);
		double leftSpeed = min(max(targetSpeed - rotateSpeed, -1), 1);
		std::printf("rotate\n");
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
		std::printf("dd\n");
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
	state = ROTATE_SPEED;
}
