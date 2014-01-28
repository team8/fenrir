#ifndef COMMAND_H
#define COMMAND_H
#include "Constants.h"

// Arguments used for Drivetrain methods
typedef struct DriveArgs {
	float driveDist;
	double rotAngle;
	double rotSpeed;
	double driveSpeed;
	float speedValue;
	float turnValue;
} DriveArgs;

typedef struct ShooterArgs {
	bool trigger;
}

typedef union {
	int a,b,c;
} Method;

/*COMMAND OBJECT*/
class RobotCommand{
	public:
		typedef enum SubsystemType{
			DRIVE,
			SHOOTER,
			ACCUMULATOR
		} SubsystemType; 
	
		/*SUBSYSTEM METHODS*/
		//These are the methods used in the Drivetrain subsystem
		typedef enum ShooterMethod {
			PREP,
			FIRE
		} ShooterMethod;

		RobotCommand(SubsystemType subsystemType, Method methodType, void * args);
		SubsystemType getSubsystem();
		Method getMethod();
		void *argPointer; // Points to argument structure
	private:
		SubsystemType subsystem; // Subsystem e command is to be sent to
		Method method; // Method to be run in the subsystem
};

typedef union Method{
	RobotCommand::DriveMethod driveMethod;
	RobotCommand::ShooterMethod shooterMethod;
	RobotCommand::AccumulatorMethod accumulatorMethod;
} Method;

#endif
