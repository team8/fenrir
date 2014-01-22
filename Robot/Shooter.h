#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

typedef enum ShooterState 
{
	SHOOTER_IDLE,  
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
		ShooterState state;
	public:
		void shoot();
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};
