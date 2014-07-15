#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#include <WPILib.h>

class XBoxController : public Joystick {
  public:
    XBoxController(uint32_t port) : Joystick(port) {}
    virtual ~XBoxController() {}
    
    /*Joystick Axes*/
    double getLeftX() { return GetRawAxis(1); }
    double getLeftY() { return GetRawAxis(2); }
    double getRightX() { return GetRawAxis(4); }
    double getRightY() { return GetRawAxis(5); }
    
    /*Joystick Triggers*/
    double getTrigger() { return GetRawAxis(3);}

    /*Buttons*/
    bool getButtonX() { return GetRawButton(3); }
    bool getButtonY() { return GetRawButton(4); }
    bool getButtonB() { return GetRawButton(2); }
    bool getButtonA() { return GetRawButton(1); }
    bool getButtonLB() { return GetRawButton(5);}
    bool getButtonRB() { return GetRawButton(6);}

};

#endif
