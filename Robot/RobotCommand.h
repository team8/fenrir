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
} DriveArgs;

typedef struct ShooterArgs {
	bool trigger;
} ShooterArgs;

/*COMMAND OBJECT*/
class RobotCommand {
	public:
		typedef enum SubsystemType {
			DRIVE,
			SHOOTER,
			ACCUMULATOR,
			RANGEFINDER.
			ROBOT
		} SubsystemType; 
	
		/*SUBSYSTEM METHODS*/
		typedef enum DriveMethod {
			SETSPEED,
			DRIVEDIST,
			ROTATEANGLE,
			ROTATESPEED,
			STOPVICTORS
		} DriveMethod;
		
		typedef enum AccumulatorMethod {
			ACCUMULATE,
			STOP,
			PASS
		} AccumulatorMethod;
		
		typedef enum ExtensionMethod {
			FOWARD,
			BACKWARD,
			HALT
		} ExtensionMethod;
		
		typedef enum ShooterMethod {
			PREP,
			FIRE
		} ShooterMethod;
		
		typedef enum RangeFinderMethod {
			ANGLE,
			SET_DIST
		};
		
		typedef enum RobotMethod {
			ALIGN_THEN_SHOOT
		};
		
		typedef union {
			DriveMethod driveMethod;
			AccumulatorMethod accumulatorMethod;
			ShooterMethod shooterMethod;
			ExtensionMethod extensionMethod;
			RangeFinderMethod rangefinderMethod;
			RobotMethod robotMethod
		} Method;

		RobotCommand(RobotCommand::SubsystemType subsystemType, Method methodType, void *args);
		SubsystemType getSubsystem();
		Method getMethod();
		void *argPointer;
	private:
		SubsystemType subsystem;
		Method method;
};

typedef union Method {
	RobotCommand::DriveMethod driveMethod;
	RobotCommand::ShooterMethod shooterMethod;
	RobotCommand::AccumulatorMethod accumulatorMethod;
} Method;

#endif
