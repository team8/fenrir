#ifndef COMMAND_H
#define COMMAND_H
#include "Constants.h"

// Arguments used for Drivetrain methods
typedef union DriveArgs {
		double driveDist;
		double rotAngle;
		double rotSpeed;
		double driveSpeed;
		double speedValue;
} DriveArgs;

typedef struct ShooterArgs {
		bool trigger;
} ShooterArgs;

typedef struct RangefinderArgs {
		float target;
} RangefinderArgs;

/*COMMAND OBJECT*/
class RobotCommand {
	public:
		typedef enum SubsystemType {
			DRIVE, SHOOTER, ACCUMULATOR, RANGEFINDER, ROBOT
		} SubsystemType;

		/*SUBSYSTEM METHODS*/
		typedef enum DriveMethod {
			SETSPEED, DRIVEDIST, ROTATEANGLE, ROTATESPEED, STOPVICTORS
		} DriveMethod;

		typedef enum AccumulatorMethod {
			ACCUMULATE, STOP, PASS
		} AccumulatorMethod;

		typedef enum ExtensionMethod {
			FOWARD, BACKWARD, HALT
		} ExtensionMethod;

		typedef enum ShooterMethod {
			FIRE, EJECT, IDLE, FLUSH, MANUAL_FIRE, MANUAL_LOAD, OUT_FLUSH
		} ShooterMethod;

		typedef enum RangefinderMethod {
			ANGLE, SET_DIST, LEFT_ON, RIGHT_ON, WALL_DIST
		};

		typedef enum RobotMethod {
			ALIGN_THEN_SHOOT
		};

		typedef union {
				DriveMethod driveMethod;
				AccumulatorMethod accumulatorMethod;
				ShooterMethod shooterMethod;
				ExtensionMethod extensionMethod;
				RangefinderMethod rangefinderMethod;
				RobotMethod robotMethod;
		} Method;

		RobotCommand(RobotCommand::SubsystemType subsystemType, Method methodType, void *args);
		RobotCommand::SubsystemType getSubsystem();
		Method getMethod();
		void *argPointer;
	private:
		RobotCommand::SubsystemType subsystem;
		Method method;
};

typedef union Method {
		RobotCommand::DriveMethod driveMethod;
		RobotCommand::ShooterMethod shooterMethod;
		RobotCommand::AccumulatorMethod accumulatorMethod;
} Method;

#endif
