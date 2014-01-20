#ifndef COMMAND_H
#define COMMAND_H
#include "Constants.h"
/*SUBSYSTEM ENUM*/
// These are the subsystems that you can send the Command to
typedef enum SubsystemType{
    DRIVE,
    SHOOTER,
    ACCUMULATOR
} SubsystemType; 

/*METHOD ENUMS*/
// These are the methods available in the Drivetrain subsystem
typedef enum DriveMethod{
  SETSPEED,
  DRIVEDIST,
  ROTATEANGLE,
  ROTATESPEED,
  STOPROTATE
}DriveMethod;

typedef enum AccumulatorMethod{
	ACCUMULATE,
	STOP
}AccumulatorMethod;

// These are the methods available in the Shooter subsystem
typedef enum ShooterMethod{
    SHOOT
}ShooterMethod;

/*METHOD ARGUMENTS*/
// Arguments available for Drivetrain methods
typedef struct DriveArgs{
  float driveDist;
  double rotAngle;
  double rotSpeed;
  double speedValue;
}DriveArgs;

// Arguments available for Shooter methods
typedef struct ShooterArgs{
    
} ShooterArgs;

typedef struct AccumulatorArgs {
	
} AccumulatorArgs;

typedef union {
    DriveArgs driveArgs;
    ShooterArgs shooterArgs;
    AccumulatorArgs accumulatorArgs;
} Args;

/*COMMAND OBJECT*/
class RobotCommand {
    public:
        RobotCommand(SubsystemType subsystemType, Method methodType, void * args);
        SubsystemType getSubsystem();
        Method getMethod();
        void * argPointer; // Points to argument struct
    private:
        SubsystemType subsystem; // Subsystem e command is to be sent to
        Method method; // Method to be run in the subsystem
};
#endif
