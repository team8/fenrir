#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Constants.h"
#include <WPILib.h>
#include "RobotCommand.h"
#include <stdlib.h>
#include <iostream>

class DriveTrain {
	private:
		// Victors 
		Victor leftFrontVic;
		Victor leftBackVic;
		Victor rightFrontVic;
		Victor rightBackVic;

		//Gyro gyroscope;

		Encoder leftEnc;
		Encoder rightEnc;

		PIDController leftFrontController;
		PIDController rightFrontController;
		PIDController leftBackController;
		PIDController rightBackController;
		//PIDController angleController;

		//target speeds 
		double targetRate;
		double targetSpeed;
		double rotateSpeed;
		double rotateAngle;
		double targetDist;

		// For testing
		double prevLeftDist;
		double prevRightDist;

		//state 
		typedef enum DriveState {
			DRIVE_DIST, ROTATE_SPEED, TURN_ANGLE, STOP_VICTORS
		} DriveState;
		DriveState state;

	public:
		DriveTrain();

		void init();
		void disable();
		/*Takes input of distance to destination
		 //Will use PID or PIDControllers to calculate input for victors. 
		 //Uses encoders as input for distance from destination*/
		void driveD(double dist);

		//Takes input of -1 to 1 and sets speed of victors. 
		//Only drives straight
		void setSpeed(double spd);

		void rotateA(double angle);

		//takes current speed, and subtracts speed one one side and increases on another. -1 is left 1 is right.
		void rotateS(double speed);

		//Stops victors
		void stopVictors();
		void update();
		void runCommand(RobotCommand command);
		double getRightEnc();
		double getLeftEnc();
};

double absolute(double n);
#endif
