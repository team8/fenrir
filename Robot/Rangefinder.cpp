#include "Rangefinder.h"

Rangefinder::Rangefinder() :
	ultraLeft((uint32_t)ULTRASONIC_CHANNEL_LEFT), // We need to figure out what channels are and give it a value
	rxLeft((uint32_t)ULTRASONIC_RX_LEFT),
	ultraRight((uint32_t)ULTRASONIC_CHANNEL_RIGHT),
	rxRight((uint32_t)ULTRASONIC_RX_RIGHT)
{
	state = IDLE;
	distInch = 0;
	leftAvg = 0;
	rightAvg = 0;
	leftTotal = 0;
	rightTotal = 0;
}

void Rangefinder::rotateToWall() {
	double leftDist = ultraLeft.GetVoltage();
	double rightDist = ultraRight.GetVoltage();
	double angle = atan((leftDist - rightDist) / ULTRA_GAP);
	
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs*) argPointer) -> rotAngle = angle;
	RobotCommand::Method method;
	method.driveMethod = RobotCommand::ROTATEANGLE;
	RobotCommand command(RobotCommand::DRIVE, method, argPointer);
	//robot -> setCommand(command);
}

float Rangefinder::wallDist() {
	double leftDist = ultraLeft.GetVoltage() * 104;
	leftAvg += leftDist;
	//std::printf("Left Ultrasonic: %f\n", leftDist);
	double rightDist = ultraRight.GetVoltage() * 104;
	rightAvg += rightDist;
	//std::printf("Right Ultrasonic: %f\n\n", rightDist);
	return ((leftDist + rightDist) / 2); // The distance to the wall from the middle of the robot
}

void Rangefinder::setDistToWall(float dist) {
	void * argPointer = malloc(sizeof(DriveArgs));
	((DriveArgs*) argPointer) -> driveDist = wallDist() - dist;
	RobotCommand::Method method;
	method.driveMethod = RobotCommand::DRIVEDIST;
	RobotCommand command(RobotCommand::DRIVE, method, argPointer);
	//robot -> setCommand(command);
}

double Rangefinder::getDist() {
	return distInch;
}

void Rangefinder::runCommand(RobotCommand command) {
	RangefinderArgs* args = (RangefinderArgs*) command.argPointer;
	switch(command.getMethod().rangefinderMethod) {
		case RobotCommand::ANGLE:
			rotateToWall();
			break;
		case RobotCommand::SET_DIST:
			setDistToWall(args -> target);
			break;
		case RobotCommand::LEFT_ON:
			rxLeft.Set(HIGH);
			break;
		case RobotCommand::RIGHT_ON:
			rxRight.Set(HIGH);
			break;
		case RobotCommand::WALL_DIST:
			distInch = 0;
			state = LEFT;
			break;
	}
}

void Rangefinder::update() {
	switch(state) {
		case IDLE:
			rxLeft.Set(HIGH);
			rxRight.Set(LOW);
			break;
		case LEFT:
			rxLeft.Set(HIGH);
			rxRight.Set(LOW);
			if (leftTotal < 10) {
				double dist = ultraLeft.GetVoltage() * 104;
				std::printf("Left: %f\n", dist);
				leftAvg += dist;
				leftTotal++; 
			}
			else {
				leftAvg /= leftTotal;
				//state = PRUNE_LEFT;
				std::printf("Left Avg: %f\n", leftAvg);
			}
			break;
//		case PRUNE_LEFT:
//			if (leftTotal < 160) {
//				leftTotal++;
//				rxRight.Set(HIGH);
//				rxLeft.Set(LOW);
//			} else {
//				state = RIGHT;
//			}
//			break;
		case RIGHT:
			rxRight.Set(HIGH);
			rxLeft.Set(LOW);
			if (rightTotal < 10) {
				double dist = ultraRight.GetVoltage() * 104;
				std::printf("Right: %f\n", dist);
				rightAvg += dist;
				rightTotal++;
			}
			else {
				rightAvg /= rightTotal;
				//state = PRUNE_RIGHT;
				std::printf("Right Avg: %f\n", rightAvg);
			}
			break;
//		case PRUNE_RIGHT:
//			state = FINISHED;
//			break;
		case FINISHED:
			rxLeft.Set(LOW);
			rxRight.Set(LOW);
			state = IDLE;
			 
			distInch = (rightAvg + leftAvg) / 2;
			std::printf("Average: %f\n\n", distInch);
			
			leftAvg = 0;
			rightAvg = 0;
			leftTotal = 0;
			rightTotal = 0;
			break;
	}
}
