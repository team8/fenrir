// fenrir.cpp

class Fenrir : public IterativeRobot {
 private:
         HumanController humanController;
         AutonomousMode mode;
         AutonomousController autoController;
         Robot robot;

 public: //need to input stuff based on the names of stuff

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
  void setCommand();
  
  Command * command;
};

Fenrir::Fenrir() :
        humanController(&robot),
        mode(DEFAULT),
        autoController(&robot, mode),
        robot()
{
}

void Fenrir:: RobotInit(){
 
}

void Fenrir:: AutonomousInit(){
 
}

void Fenrir:: AutonomousPeriodic(){
 setCommand();
}

void Fenrir:: AutonomousDisabled(){
 
}

void Fenrir:: DisabledInit(){
 
}

void Fenrir:: DisabledPeriodic(){
 
}

void Fenrir:: TeleopInit(){
 
}

void Fenrir:: TeleopPeriodic(){
 setCommand();
}

void Fenrir:: TeleopDisabled(){
 
}

void Fenrir:: TestInit(){
 
}

void Fenrir:: TestPeriodic(){
 
}

void setCommand() {
  command = autoController.getCommand();
 if (command != NULL) {
  if (command.getSubsystem() == DRIVE) {
   // Send command to drivetrain.cpp
  } // Add more if loops here for other subsystems when they exist
 }
}
