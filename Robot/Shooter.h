#include "WPILib.h"
#include "Constants.h"

class Shooter {
 
 private:
  
  Victor vic1;
  Victor vic2;
  Victor vic3;
  Victor vic4;
  
 public:
 
  void shoot();
  void update();
  Shooter();
 
};
