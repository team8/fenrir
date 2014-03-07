#ifndef SHOOTER_H
#define SHOOTER_H
#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"
#include <stdlib.h>

class Robot;


class Shooter {
	private:
		bool isShooting;
	
		Robot* robot;
		Victor shooterVic1;
		Victor shooterVic2;
		Victor shooterVic3;
		Victor shooterVic4;
		
		Victor loaderVic;
		
		Encoder encShooter1;
		Encoder encShooter2;
		Encoder encShooter3;
		Encoder encShooter4;
		
		PIDController encController1;
		PIDController encController2;
		PIDController encController3;
		PIDController encController4;
		
		double loadSpeed;
		
		typedef enum ShooterState {
			IDLE,
			PREPARING,
			FIRING,
			EJECT,
			FLUSH
		} ShooterState;
		ShooterState state;
		
		Timer shootTimer;
	public:
		void startShooterVics(double speed);
		void setAllVics(double speed);
		void update();
		Shooter();
		void runCommand(RobotCommand command);
		void eject();
};

#endif
