#include "Constants.h"

/*SUBSYSTEM ENUM*/
// These are the subsystems that you can send the Command to
typedef enum {
    DRIVE,
    SHOOTER
} SubsystemType;

/*METHOD ENUMS*/
// These are the methods available in the Drivetrain subsystem
typedef enum {
    DRIVESPEED,
    DRIVEDIST,
    ROTATEANGLE,
    ROTATESPEED
} DriveMethod;

// These are the methods available in the Shooter subsystem
typedef enum {
    SHOOT
} ShooterMethod;

typedef union {
    DriveArgs driveArgs;
    ShooterArgs shooterArgs;
} Args;

/*METHOD ARGUMENTS*/
// Arguments available for Drivetrain methods
typedef struct {
    double driveSpeed;
    double driveDist;
    double rotAngle;
    float turnValue;
    float speedValue;
} DriveArgs;

// Arguments available for Shooter methods
typedef struct {
    
} ShooterArgs;

/*COMMAND OBJECT*/
class Command {
    public:
        Command(bool inAuto);
        Command(bool inAuto, SubsystemType subsystemType, int methodType, void * args);
        void command(SubsystemType subsystem, int methodEnum, void * args);
        int getSubsystem();
        int getMethod();
        bool getParent();
        void * argPointer; // Points to argument struct
    private:
        int subsystem; // Subsystem e command is to be sent to
        int method; // Method to be run in the subsystem
        bool parent; // True if autonomous, false if teleop
}
