#include "Constants.h"
#include <WPILib.h>

class DriveTrain {
    private:
    
    // Victors
    LinearVictor leftFrontVic;
    LinearVictor leftBackVic;
    LinearVictor rightFrontVic;
    LinearVictor rightBackVic;
    
    // Encoders
    Encoder leftEnc;
    Encoder rightEnc;
    
    // Needs speed controller stuff
    
    public:
    
    DriveTrain();
    void driveD(double dist);
    void setSpeed(double spd);
    void rotateA(double angle);
    void rotateS(double rotspd);
    void update();
    void runMethod(int methodNum, int passValue);
}
