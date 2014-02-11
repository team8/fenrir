#include "Constants.h"
#include "Robot.h"
#include "HumanController.h"
#include "AutonomousController.h"

class Fenrir : public IterativeRobot {
	private:
		Robot robot;
		HumanController humanController;
		AutonomousController autoController;
		Timer time;
	public:
		Fenrir();
		void RobotInit();
		void AutonomousInit();
		void AutonomousPeriodic();
		void AutonomousDisabled();
		void DisabledInit();
		void DisabledPeriodic();
		void TeleopInit();
		void TeleopPeriodic();
		void TeleopDisabled();
		void TestInit();
		void TestPeriodic();
};

Fenrir::Fenrir():
	robot(),
	humanController(&robot),
	autoController(&robot),
	time()
{

}

void Fenrir::RobotInit() {
}

void Fenrir::AutonomousInit() {
	time.Start();
}

void Fenrir::AutonomousPeriodic() {
	autoController.update();
	robot.update();
}

void Fenrir::AutonomousDisabled() {
	
}

void Fenrir::DisabledInit() {
	robot.disable();
}

void Fenrir::DisabledPeriodic() {
	robot.disable();
	robot.update();
}

void Fenrir::TeleopInit() {
	robot.init();

}

void Fenrir::TeleopPeriodic() {
	humanController.update();
	robot.update();
}

void Fenrir::TeleopDisabled() {
	
}

void Fenrir::TestInit() {
	
}

void Fenrir::TestPeriodic() {
	
}

START_ROBOT_CLASS(Fenrir);
