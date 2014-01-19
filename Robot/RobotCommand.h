#ifndef COMMAND_H
#define COMMAND_H
#include "Constants.h"
/*SUBSYSTEM ENUM*/
// These are the subsystems that you can send the Command to
typedef enum {
    DRIVE,
    SHOOTER,
    ACCUMULATOR
} SubsystemType; 

/*METHOD ENUMS*/
// These are the methods available in the Drivetrain subsystem
typedef enum {
    DRIVEDIST,
    ROTATEANGLE,
    ROTATESPEED,
    SETSPEED,
} DriveMethod;

// These are the methods available in the Shooter subsystem
typedef enum {
    SHOOT
}ShooterMethod;

/*METHOD ARGUMENTS*/
// Arguments available for Drivetrain methods
typedef struct {
	
    double driveDist;
    double rotAngle;
    float turnValue;
    float speedValue;
} DriveArgs;

// Arguments available for Shooter methods
typedef struct {
    
} ShooterArgs;

typedef union {
    DriveArgs driveArgs;
    ShooterArgs shooterArgs;
} Args;

/*COMMAND OBJECT*/
class RobotCommand {
    public:
        RobotCommand(bool inAuto);
        RobotCommand(bool inAuto, SubsystemType subsystemType, int methodType, void * args);
        void command(SubsystemType subsystem, int methodEnum, void * args);
        SubsystemType getSubsystem();
        int getMethod();
        bool getParent();
        void * argPointer; // Points to argument struct
    private:
        SubsystemType subsystem; // Subsystem e command is to be sent to
        int method; // Method to be run in the subsystem
        bool parent; // True if autonomous, false if teleop
};
#endif
