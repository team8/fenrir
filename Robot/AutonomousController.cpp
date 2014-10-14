#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) 
{
	timerStarted = true;
	shootInAuto = false;
	std::printf("Autonomous controller constructor\n");
	this->robot = robotPointer;
	time.Reset();
}

bool AutonomousController::shoot() {
	return false;
}

/*Premade paths depending on where we start left-to-right*/
void AutonomousController::pathOne(){

	//Drive into position
	void *argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = 100; //This value is not confirmed
	RobotCommand::Method driveDist;
	driveDist.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, driveDist, argPointer);
	robot -> setCommand(positionCommand);

	//Use rangefinders to calibrate exactly
//	RobotCommand::Method findRange;
//	findRange.rangefinderMhggethod = RobotCommand::WALL_DIST;
//	RobotCommand alignCommand(RobotCommand::RANGEFINDER, findRange, 0);
//	robot -> setCommand(alignCommand);
}

void AutonomousController::update() {
	if(timerStarted){
		time.Start();
		timerStarted = false;

	}
//	if(shootInAuto) {
//				RobotCommand::Method fireShooter;
//				fireShooter.shooterMethod = RobotCommand::FIRE;
//				RobotCommand fireCommand(RobotCommand::SHOOTER, fireShooter, 0);
//				robot -> setCommand(fireCommand);
//	}
	//if()
	//Runs all methods according to time
	if(time.Get() <= 2) {
		void * argPointer = malloc(sizeof(DriveArgs));
		((DriveArgs*) argPointer)->speedValue = -.7;
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot->setCommand(speedCommand);
		
		((DriveArgs*) argPointer)->rotSpeed = 0;
		RobotCommand::Method setRotate;
		setRotate.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotCommand(RobotCommand::DRIVE, setRotate, argPointer);
		robot->setCommand(rotCommand);\
	//	std::printf("Right: %f Left: %f \n", robot->getRightEnc(), robot->getLeftEnc());
	} else {
		//cout << "Stopping" << endl;
		void * argPointer = malloc(sizeof(DriveArgs));
		((DriveArgs *) argPointer) -> speedValue = 0;
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot -> setCommand(positionCommand);
		
		((DriveArgs*) argPointer)->rotSpeed = 0;
		RobotCommand::Method setRotate;
		setRotate.driveMethod = RobotCommand::ROTATESPEED;
		RobotCommand rotCommand(RobotCommand::DRIVE, setRotate, argPointer);
		robot -> setCommand(rotCommand);
	}
}
