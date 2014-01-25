#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState {
	IDLE,  
	CHECK_LOADED,
	PREP,
	SHOOTING
}ShooterState;

class Shooter {
	private:
		Victor shooterVic1;
		Victor shooterVic2;
		Victor shooterVic3;
		Victor shooterVic4;
		
		Victor loaderVic1;
		Victor loaderVic2;
		
		ShooterState state;
		
		void setAllVics();
		void setShooterVics(float speed);
		void shoot();
		
		Timer time;
	public:
		void shoot();
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};

