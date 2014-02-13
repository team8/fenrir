#include "DriveTrain.h"

DriveTrain::DriveTrain() :		
	// Victors
	leftFrontVic((uint32_t) PORT_DRIVE_VIC_1),
	leftBackVic((uint32_t) PORT_DRIVE_VIC_2),
	rightFrontVic((uint32_t) PORT_DRIVE_VIC_3),
	rightBackVic((uint32_t) PORT_DRIVE_VIC_4),

	gyroscope((uint32_t) PORT_GYRO),

	// Encoders
	leftEnc((uint32_t) PORT_ENCODER_LEFT_A,(uint32_t) PORT_ENCODER_LEFT_B, true),
	rightEnc((uint32_t) PORT_ENCODER_RIGHT_A,(uint32_t) PORT_ENCODER_RIGHT_B, true),

	// PIDControllers
	leftController(0.1, 0.1, 0.1, &leftEnc, &leftBackVic),
	rightController(0.1, 0.1, 0.1, &rightEnc, &rightBackVic)
	//angleController(0.1, 0.1, 0.1, &gyroscope, &leftBackVic) 
{
	//gyroscope.Start();
	rightController.SetOutputRange(-1, 1);
    //angleController.SetOutputRange(-1, 1);
}

void DriveTrain::init() {
		std::printf("leftEnc: %i\n", (int)&leftEnc);
		std::printf("rightEnc: %i\n", (int)&rightEnc);
		std::printf("leftBackVic: %i\n", (int)&leftBackVic);
		std::printf("rightBackVic: %i\n", (int)&rightBackVic);
		
		rightEnc.Start();
		leftEnc.Start();
		std::printf("Initialized\n");
		rightEnc.SetDistancePerPulse(1.0);
		leftEnc.SetDistancePerPulse(1.0);
		rightEnc.SetPIDSourceParameter(PIDSource::kDistance);
		leftEnc.SetPIDSourceParameter(PIDSource::kDistance);
}

//runs method according to what newCommand is received
void DriveTrain::runCommand(RobotCommand command) {

	DriveArgs* args = (DriveArgs*) command.argPointer;
	switch (command.getMethod().driveMethod) {
	case RobotCommand::SETSPEED:

		std::printf("leftEnc: %f\n", leftEnc.GetDistance());
		std::printf("rightEnc: %f\n", rightEnc.GetDistance());
		std::printf("SETSPEED is running\n");
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
	
	std::printf("rightbackvic: %i\n", (int)rightBackVic.CheckDigitalChannel(2));
	std::printf("leftBackVic: %i\n", (int)leftBackVic.CheckDigitalChannel(1));
	
	switch (state) {

	case ROTATE_SPEED:
		double rightSpeed = min(max(-(targetSpeed + rotateSpeed), -1), 1);
		double leftSpeed = min(max(targetSpeed - rotateSpeed, -1), 1);
		leftFrontVic.Set(leftSpeed);
		leftBackVic.Set(leftSpeed);
		rightFrontVic.Set(rightSpeed);
		rightBackVic.Set(rightSpeed);
		std::printf("leftSpeed: %f\n", leftSpeed);
		std::printf("rightSpeed: %f\n", rightSpeed);
		break;

	case DRIVE_DIST:
		leftFrontVic.Set(leftEnc.PIDGet());
		leftBackVic.Set(leftEnc.PIDGet());
		rightFrontVic.Set(-(rightEnc.PIDGet()));
		rightBackVic.Set(-(rightEnc.PIDGet()));
		std::printf("leftEncPIDGet: %f\n", leftEnc.PIDGet());
		std::printf("rightEncPIDGet: %f\n", rightEnc.PIDGet());
		std::printf("leftpidctrl.Get: %f\n", leftController.Get());
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
	leftController.SetSetpoint(dist);
	rightController.SetSetpoint(dist);
	leftController.Enable();
	rightController.Enable();
	std::printf("DriveTrain::driveD. encoders reset\n");
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
