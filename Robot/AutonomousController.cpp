#include "AutonomousController.h"
#include "Constants.h"

AutonomousController::AutonomousController(Robot *robotPointer) {
	pathCalled = false;
	hasShot = false;
	std::printf("Autonomous controller constructor\n");
	this -> robot = robotPointer;
	//we shoot from about 10 feet, will modify as needed
	shootDist = 120;
	spawnDist = 218;
	time.Stop();
	time.Reset();
}

void AutonomousController::path() {
	//TODO:find the distances, and see if shoot can run simultaneously
	void * argPointer = malloc(sizeof(DriveArgs));

	//if(robot->getLeftEnc()!= 45 && robot->getRightEnc() != 45) {
	//	double average = (robot->getLeftEnc() + robot->getRightEnc())/2;
		
	((DriveArgs*)argPointer) -> driveDist = 20;
	RobotCommand::Method setSpeed;
	setSpeed.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand speedCommand(RobotCommand::DRIVE, setSpeed, argPointer);
	robot -> setCommand(speedCommand);
	

	//Drive into position
//	void * argPointer = malloc(sizeof(DriveArgs));
//	//((DriveArgs *) argPointer) -> speedValue = -0.3; //This value is confirmed
//	((DriveArgs *) argPointer) -> driveDist = 45;
//	RobotCommand::Method driveDist;
//	driveDist.driveMethod = RobotCommand::DRIVEDIST;
//	RobotCommand positionCommand(RobotCommand::DRIVE, driveDist, argPointer);
//	robot -> setCommand(positionCommand);
	
//	RobotCommand::Method setSpeed;
//	setSpeed.driveMethod = RobotCommand::SETSPEED;
//	RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
//	robot -> setCommand(positionCommand);
//	
	//RobotCommand::Method shoot;
	//shoot.shooterMethod = RobotCommand::FIRE;
	//RobotCommand command(RobotCommand::RobotCommand::SHOOTER, shoot, 0);
	//robot -> setCommand(command);
}

void AutonomousController::update() {
//	if (!pathCalled) {
//		path();
//		pathCalled = true;
//	}
	/*BACKUP CODE*/
	void * argPointer = malloc(sizeof(DriveArgs));
	
	time.Start();
	if(time.Get() < 3) {
		((DriveArgs *) argPointer) -> speedValue = -0.3;
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot -> setCommand(positionCommand);
	} 
	else {
		((DriveArgs *) argPointer) -> speedValue = 0;
		RobotCommand::Method setSpeed;
		setSpeed.driveMethod = RobotCommand::SETSPEED;
		RobotCommand positionCommand(RobotCommand::DRIVE, setSpeed, argPointer);
		robot -> setCommand(positionCommand);
		
		RobotCommand::Method accumulate;
		accumulate.accumulatorMethod = RobotCommand::ACCUMULATE;
		RobotCommand accumCommand(RobotCommand::ACCUMULATOR, accumulate, 0);
		robot -> setCommand(accumCommand);
		
		if(!hasShot){
			RobotCommand::Method fire;
			fire.shooterMethod = RobotCommand::FIRE;
			RobotCommand fireCommand(RobotCommand::SHOOTER, fire, 0);
			robot -> setCommand(fireCommand);
			hasShot = true;
		}
		
	//	std::printf("Right: %f Left: %f \n", robot->getRightEnc(), robot->getLeftEnc());
	}

}
