#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#include <WPILib.h>

class XBoxController : public Joystick {
  public:
    XBoxController(uint32_t port) : Joysitck(port) {}
    virtual ~XBoxController() {}
    
    /*Joystick Axes*/
    double getLeftX() { return GetRawAxis(1); }
    double getLeftY() { return GetRawAxis(2); }
    double getRightX() { return GetRawAxis(4); }
    double getRightY() { return GetRawAxis(5); }
    
    /*Letter Buttons*/
    bool getButtonX() { return GetRawButton(3); }
    bool getButtonY() { return GetRawButton(4); }
    bool getButtonB() { return GetRawButton(2); }
    bool getButtonA() { return GetRawButton(1); }

    /*Arrow-Key Pad*/
    
};

#endif
