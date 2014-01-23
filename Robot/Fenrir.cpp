#include "Constants.h"
#include "Robot.h"
#include "HumanController.h"
#include "AutonomousController.h"
// fenrir.cpp

class Fenrir : public IterativeRobot {
 private:
         HumanController humanController;
         AutonomousController autoController;
         Robot robot;

 public: //need to input stuff based on the names of stuff
        Fenrir();
 //make sure we call the methods like this.
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

Fenrir::Fenrir() :
        humanController(&robot),
        autoController(&robot),
        robot()
{

}

void Fenrir::RobotInit(){
 
}

void Fenrir::AutonomousInit(){

}

void Fenrir::AutonomousPeriodic(){

}

void Fenrir::AutonomousDisabled(){
 
}

void Fenrir::DisabledInit(){
 
}

void Fenrir::DisabledPeriodic(){
 
}

void Fenrir::TeleopInit(){
 
}

void Fenrir::TeleopPeriodic(){

}

void Fenrir::TeleopDisabled(){
 
}

void Fenrir::TestInit(){
 
}

void Fenrir::TestPeriodic(){
 
}

START_ROBOT_CLASS(Fenrir);
