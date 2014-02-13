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
	autoController(&robot)
{
	std::printf("Fenrir constructor\n");
}

void Fenrir::RobotInit() {
	std::printf("Robot init\n");
}

void Fenrir::AutonomousInit() {
	std::printf("auto init\n");
	time.Start();
}

void Fenrir::AutonomousPeriodic() {
	autoController.update();
	robot.update();
}

void Fenrir::AutonomousDisabled() {
	std::printf("auto disabled\n");
}

void Fenrir::DisabledInit() {
	std::printf("disabled init\n");
	robot.disable();
}

void Fenrir::DisabledPeriodic() {
	robot.disable();
	robot.update();
}

void Fenrir::TeleopInit() {
	std::printf("teleop init\n");
	robot.init();

}

void Fenrir::TeleopPeriodic() {
	humanController.update();
	robot.update();
}

void Fenrir::TeleopDisabled() {
	std::printf("teleop disabled\n");
}

void Fenrir::TestInit() {
	std::printf("test init\n");
}

void Fenrir::TestPeriodic() {
	
}

START_ROBOT_CLASS(Fenrir);
