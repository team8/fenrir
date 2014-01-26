#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState {
	NOT_SHOOTING, //see below
	CHECK_LOADED,
	PREPARING_TO_SHOOT,
	FIRING//need a better name... only did this to resolve conflict w/ ShooterMethod in RobotCommand.h
}ShooterState;

class Shooter {
	private:
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
		
		ShooterState state;
		
		Timer time;
	public:
		void shoot();
		void startShooterVics(float speed);
		void setAllVics(float speed);
		void setShooterVics(float speed);
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};
