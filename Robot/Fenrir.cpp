#include "Constants.h"
#include "Robot.h"
#include "HumanController.h"
#include "AutonomousController.h"

class Fenrir : public IterativeRobot {
	private:
		HumanController humanController;
		AutonomousController autoController;
		Robot robot;

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
	humanController(&robot),
	autoController(&robot),
	robot()
{

}

void Fenrir::RobotInit(){
	robot();
}

void Fenrir::AutonomousInit(){
	autoController(&robot);
}

void Fenrir::AutonomousPeriodic(){
	autoController.update();
	robot.update();
}

void Fenrir::AutonomousDisabled(){
	robot.disable();
}

void Fenrir::DisabledInit(){
	robot();
	robot.disable();
}

void Fenrir::DisabledPeriodic(){
	robot.disable();
	robot.update();
}

void Fenrir::TeleopInit(){
 	humanController(&robot);
}

void Fenrir::TeleopPeriodic(){
	humanController.update();
	robot.update();
}

void Fenrir::TeleopDisabled(){
	robot.disable();
}

void Fenrir::TestInit(){
	
}

void Fenrir::TestPeriodic(){
	
}

START_ROBOT_CLASS(Fenrir);
