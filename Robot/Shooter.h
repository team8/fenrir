#include "WPILib.h"

class Shooter {
 
 private:
  
  Victor motor1;
  Victor motor2;
  Victor motor3;
  Victor motor4;
  
 public:
 
  void shoot();
  void update();
 
  Shooter();
 
};
