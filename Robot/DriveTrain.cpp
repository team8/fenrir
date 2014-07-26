#include "DriveTrain.h"

DriveTrain::DriveTrain() : // Victors
			leftFrontVic((uint32_t) PORT_DRIVE_VIC_LEFT_FRONT),
			leftBackVic((uint32_t) PORT_DRIVE_VIC_LEFT_BACK),
			rightFrontVic((uint32_t) PORT_DRIVE_VIC_LEFT_FRONT),
			rightBackVic((uint32_t) PORT_DRIVE_VIC_RIGHT_BACK),

			//gyroscope((uint32_t) PORT_GYRO),

			// Encoders
			leftEnc((uint32_t) PORT_ENCODER_LEFT_A, (uint32_t) PORT_ENCODER_LEFT_B, false),
			rightEnc((uint32_t) PORT_ENCODER_RIGHT_A, (uint32_t) PORT_ENCODER_RIGHT_B, true),

			// PIDControllers
			leftFrontController(0.1, 0.01, 0.1, &leftEnc, &leftBackVic),
			rightFrontController(0.1, 0.01, 0.1, &rightEnc, &rightBackVic),
			leftBackController(0.1, .01, .1, &leftEnc, &leftFrontVic),
			rightBackController(.1, .01, .1, &rightEnc, &rightBackVic)
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
	leftFrontController.Reset();
	rightFrontController.Reset();
	leftBackController.Reset();
	rightBackController.Reset();
	leftFrontController.Enable();
	rightFrontController.Enable();
	leftBackController.Enable();
	rightBackController.Enable();
	state = STOP_VICTORS;
}

void DriveTrain::disable() {
	leftFrontController.Disable();
	rightFrontController.Disable();
	leftBackController.Disable();
	rightBackController.Disable();
	stopVictors();
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

	switch (state) {
		case ROTATE_SPEED:

			/*
			 *Logic: Take speed you want to generally go at (targetSpeed)
			 *Logic: leftVic goes positive, rightVic goes negative
			 *Logic: Vics are restricted to -1,1, so min-max to that range
			 *Logic: Take targetSpeed and add/subtract rotateSpeed for turning
			 *Logic: Right victor is negative because we are turning
			 */
//						double leftSpeed = min(max(targetSpeed - rotateSpeed, -1), 1);
//						double rightSpeed = min(max(targetSpeed + rotateSpeed, -1), 1);
//						leftFrontVic.Set(-leftSpeed);
//						leftBackVic.Set(-leftSpeed);
//						rightFrontVic.Set(rightSpeed);
//						rightBackVic.Set(rightSpeed);

			leftFrontVic.Set(leftFrontController.Get());
			leftBackVic.Set(leftBackController.Get());
			rightFrontVic.Set(-rightFrontController.Get());
			rightBackVic.Set(-rightBackController.Get());
			std::cout << "leftFrontPID: " << leftFrontController.Get() << std::endl;
			std::cout << "rightFrontPID: " << rightFrontController.Get() << std::endl;
			std::cout << "supposed rate: " << leftFrontController.GetSetpoint() << std::endl;
		break;

		case DRIVE_DIST:
			rightFrontVic.Set(-rightFrontController.Get());
			rightBackVic.Set(-rightBackController.Get());
			leftFrontVic.Set(leftFrontController.Get());
			leftBackVic.Set(leftBackController.Get());

		break;

		case TURN_ANGLE:
			//		leftFrontVic.Set(-(angleController.Get()));
			//		leftBackVic.Set(-(angleController.Get()));
			//		rightFrontVic.Set(angleController.Get());
			//		rightBackVic.Set(angleController.Get());
		break;

		case STOP_VICTORS:
			leftFrontVic.Set(0.0);
			leftBackVic.Set(0.0);
			rightFrontVic.Set(0.0);
			rightBackVic.Set(0.0);
		break;
	}
}
//Drives robot certain distance
//Will use PID to determine output for victors
//Uses encoders
void DriveTrain::driveD(double dist) {
	leftEnc.Reset();
	rightEnc.Reset();
	leftFrontController.Reset();
	leftBackController.Reset();
	rightFrontController.Reset();
	rightBackController.Reset();
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

	double rate = spd * CIM_MAX_RATE;
	if (::absolute(rate) <= 0.01) { rate = 0; }
	targetRate = rate;
	leftFrontController.SetSetpoint(targetRate);
	rightFrontController.SetSetpoint(targetRate);
	leftBackController.SetSetpoint(targetRate);
	rightBackController.SetSetpoint(targetRate);
	std::cout << "rate: " << rate << std::endl;
	std::cout << "targetRate: " << targetRate << std::endl;
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
	leftFrontVic.Set(0.0);
	leftBackVic.Set(0.0);
	rightFrontVic.Set(0.0);
	rightBackVic.Set(0.0);
	state = STOP_VICTORS;
}

double DriveTrain::getRightEnc() {
	return rightEnc.GetDistance();
}

double DriveTrain::getLeftEnc() {
	return leftEnc.GetDistance();
}

double absolute(double n) {
	if (n < 0) {
		return -n;
	}
	return n;
}

