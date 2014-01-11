class HumanController {

 public:

  void update();
  HumanController(Robot *robotPointer);

 private:
  
  Robot *robot;
  Joystick speedStick;
  Joystick turnStick;
  Joystick operatorStick;

};


