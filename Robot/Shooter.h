#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState {
	NOT_SHOOTING, //see below
	CHECK_LOADED,
	PREP,
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
		
		Encoder encShooter;
		
		ShooterState state;
		
		Timer time;
	public:
		void shoot();
		void setAllVics(float speed);
		void setShooterVics(float speed);
		void getShooterEncs(float encSpeed);
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};
