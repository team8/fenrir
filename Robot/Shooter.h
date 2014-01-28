#include <WPILib.h>
#include "Constants.h"
#include "RobotCommand.h"

//


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
		typedef enum ShooterState {
			IDLE,
			PREPARING,
			FIRING
		} ShooterState;
		Timer time;
	public:
		void shoot();
		void startShooterVics(float speed);
		void setAllVics(float speed);
		void update();
		Shooter();
		void runCommand(RobotCommand command);
};
