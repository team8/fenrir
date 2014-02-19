#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) {
	std::printf("Autonomous controller constructor\n");
	this -> robot = robotPointer;
}  

void AutonomousController::startTimer() {
	time.Start();
}

void AutonomousController::drive(float v) {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveSpeed = v;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::SETSPEED;
	RobotCommand command(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(command);
}

void AutonomousController::stop() {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveSpeed = 0;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::SETSPEED;
	RobotCommand stopCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(stopCommand);
}

bool AutonomousController::shoot() {
	return false;
}

/*Premade paths depending on where we start left-to-right*/
void AutonomousController::pathOne(){
	//PLS NOTE: NOT CORRECT: Use the correct commands as appropriate
	
	//Drive into position
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = 10;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);
	
	//Use rangefinders to calibrate exactly
	RobotCommand::Method findRange;
	findRange.rangefinderMethod = RobotCommand::WALL_DIST;
	RobotCommand alignCommand(RobotCommand::RANGEFINDER, findRange, 0);
	robot -> setCommand(alignCommand);
	
	//Shoot
	RobotCommand::Method shoot;
	shoot.shooterMethod = RobotCommand::FIRE;
	RobotCommand shootCommand(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	robot -> setCommand(shootCommand);
}

void AutonomousController::pathTwo() {
	//PLS NOTE: NOT CORRECT: Use the correct commands as appropriate
	
	//Drive into position
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = 10;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);
	
	//Use rangefinders to calibrate exactly
	RobotCommand::Method findRange;
	findRange.rangefinderMethod = RobotCommand::WALL_DIST;
	RobotCommand alignCommand(RobotCommand::RANGEFINDER, findRange, 0);
	robot -> setCommand(alignCommand);
	
	//Shoot
	RobotCommand::Method shoot;
	shoot.shooterMethod = RobotCommand::FIRE;
	RobotCommand shootCommand(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	robot -> setCommand(shootCommand);
}

void AutonomousController::pathThree() {
	//PLS NOTE: NOT CORRECT: Use the correct commands as appropriate
	
	//Drive into position
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs *) argPointer) -> driveDist = 10;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(positionCommand);
	
	//Use rangefinders to calibrate exactly
	RobotCommand::Method findRange;
	findRange.rangefinderMethod = RobotCommand::WALL_DIST;
	RobotCommand alignCommand(RobotCommand::RANGEFINDER, findRange, 0);
	robot -> setCommand(alignCommand);
	
	//Shoot
	RobotCommand::Method shoot;
	shoot.shooterMethod = RobotCommand::FIRE;
	RobotCommand shootCommand(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	robot -> setCommand(shootCommand);
}

void AutonomousController::update() {
	//Runs all methods according to time
//	if(time.HasPeriodPassed(5)) { // modify time value
//		void * argPointer = malloc(sizeof(DriveArgs));
//		//shootDist= will add more stuff later(the purpose of this is to find the distance until the robot is at the right distance to shoot using the angle of shot and height of goal)
//		((DriveArgs *) argPointer) -> driveDist = 5; //how far to go to get into zone
//		RobotCommand::Method driveDist;
//		driveDist.driveMethod = RobotCommand::DRIVEDIST;
//		RobotCommand command(RobotCommand::DRIVE, driveDist, argPointer);
//	}
}
