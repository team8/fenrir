#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState {
	IDLE,  
	LOADED,
	AIMING,
	SPINNING_UP,
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
		void setAllVics(float speed);
		void setShooterVics(float speed);
		double setVicsSpeed;
	public:
		void shoot();
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};
