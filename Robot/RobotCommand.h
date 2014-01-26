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
// These are the methods used in the Drivetrain subsystem
typedef enum DriveMethod{
	SETSPEED,
	DRIVEDIST,
	ROTATEANGLE,
	ROTATESPEED,
	STOPVICTORS
} DriveMethod;

//Methods used for the Accumulator
typedef enum AccumulatorMethod{
	ACCUMULATE,
	STOP,
	PASS
} AccumulatorMethod;

typedef enum AccumulatorExtensionMethod{
	FOWARD,
	BACKWARD,
	HALT
};

// These are the methods available in the Shooter subsystem
typedef enum ShooterMethod{
	PREP,
	FIRE,
} ShooterMethod;

typedef union Method{
	DriveMethod driveMethod;
	ShooterMethod shooterMethod;
	AccumulatorMethod accumulatorMethod;
	AccumulatorExtensionMethod extensionMethod;
} Method;

/*METHOD ARGUMENTS*/
// Arguments used for Drivetrain methods
typedef struct DriveArgs{
	float driveDist;
	double rotAngle;
	double rotSpeed;
	double driveSpeed;
	float speedValue;
	float turnValue;
} DriveArgs;

// Arguments used for Shooter methods
typedef struct ShooterArgs{
    bool trigger;
} ShooterArgs;

typedef struct AccumulatorArgs {
	
} AccumulatorArgs;

typedef union {
	DriveArgs driveArgs;
	ShooterArgs shooterArgs;
	AccumulatorArgs accumulatorArgs;
} Args;

/*COMMAND OBJECT*/
class RobotCommand{
	public:
		RobotCommand(SubsystemType subsystemType, Method methodType, void * args);
		SubsystemType getSubsystem();
		Method getMethod();
		void * argPointer; // Points to argument structure
	private:
		SubsystemType subsystem; // Subsystem e command is to be sent to
		Method method; // Method to be run in the subsystem
};
#endif
