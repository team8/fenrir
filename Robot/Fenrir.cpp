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

}

void Fenrir::RobotInit() {

}

void Fenrir::AutonomousInit() {
	time.Start();
	std::printf("Autonomous INITTED \n");
}

void Fenrir::AutonomousPeriodic() {
	autoController.update();
	robot.update();
	//std::printf("Time: %f\n", time.Get());
	std::printf("%f\n", time.GetFPGATimestamp());
}

void Fenrir::AutonomousDisabled() {
	robot.disable();
}

void Fenrir::DisabledInit() {
	robot.disable();
}

void Fenrir::DisabledPeriodic() {
	robot.disable();
	robot.update();
}

void Fenrir::TeleopInit() {


}

void Fenrir::TeleopPeriodic() {
	humanController.update();
	robot.update();
}

void Fenrir::TeleopDisabled() {
	robot.disable();
}

void Fenrir::TestInit() {
	
}

void Fenrir::TestPeriodic() {
	
}

START_ROBOT_CLASS(Fenrir);
