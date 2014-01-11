class AutonomousController {

 public:

  AutonomousController(Robot *robotPointer);
  void update();

 private:
 
  Timer time; 
  Robot *robot;
  
  

};
