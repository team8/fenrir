class AutonomousController {

 public:

  AutonomousController(Robot *robotPointer);
  void update();

 private:
 
  Timer time; 
  Robot *robot;
  void drive();
  void stop();
  bool shoot();
  
  bool targetReached;

};
