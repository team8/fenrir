#ifndef SHOOTER_H
#define SHOOTER_H
#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

class Robot;


class Shooter {
	private:
		bool aligned;
	
		Robot* robot;
		Victor shooterVic1;
		Victor shooterVic2;
		Victor shooterVic3;
		Victor shooterVic4;
		
		Victor loaderVic1;
		Victor loaderVic2;
		
		Encoder encShooter1;
		Encoder encShooter2;
		Encoder encShooter3;
		Encoder encShooter4;
		Timer timer;
		
		PIDController encController1;
		PIDController encController2;
		PIDController encController3;
		PIDController encController4;
		
		double loadSpeed;
		
		typedef enum ShooterState {
			IDLE,
			ALIGN,
			PREPARING,
			FIRING
		} ShooterState;
		ShooterState state;
		
		Timer time;
	public:
		void shoot();
		void startShooterVics(float speed);
		void setAllVics(float speed);
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};

#endif
