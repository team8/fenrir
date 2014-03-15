#include "Constants.h"
#include "Robot.h"
#include "HumanController.h"
#include "AutonomousController.h"
#include "Rangefinder.h"

class Fenrir: public IterativeRobot {
private:
	Robot robot;
	HumanController humanController;
	AutonomousController autoController;
	Timer time;
public:
	Fenrir();

	//All the Robot phases
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
	robot(), humanController(&robot), autoController(&robot) {
	std::printf("Fenrir constructor new robot\n");
}

void Fenrir::RobotInit() {
	std::printf("initializing robot correctly\n");
	robot.init();
}

void Fenrir::AutonomousInit() {
	time.Start();
	robot.init();
}

void Fenrir::AutonomousPeriodic() {
	autoController.update();
	robot.update();
}

void Fenrir::AutonomousDisabled() {
	std::printf("Autonomous disabled\n");
}

void Fenrir::DisabledInit() {
	std::printf("Disabled initted\n");
	robot.disable();
}

void Fenrir::DisabledPeriodic() {
	robot.disable();
	robot.update();
}

void Fenrir::TeleopInit() {
	std::printf("Teleop initialized\n");
	robot.init();
}

void Fenrir::TeleopPeriodic() {
	humanController.update();
	robot.update();
}

void Fenrir::TeleopDisabled() {
	std::printf("Teleop disabled\n");
}

void Fenrir::TestInit() {
}

void Fenrir::TestPeriodic() {
}

START_ROBOT_CLASS(Fenrir);
