#ifndef AUTONOMOUSCONTROLLER_H
#define	AUTONOMOUSCONTROLLER_H
#include "Constants.h"
#include "RobotCommand.h"
#include "Robot.h"
#include <WPILib.h>

// These are the methods for the Shooter subsystem
typedef enum ShooterMethod {
	PREP,
	FIRE
} ShooterMethod;

typedef enum {
	SETSPEED,
	DRIVEDIST,
	ROTATEANGLE,
	ROTATESPEED,
	STOPVICTORS
} DriveMethod;

typedef enum{
        ACCUMULATE,
        STOP,
        PASS
} AccumulatorMethod;

typedef enum{
        FOWARD,
        BACKWARD,
        HALT
}ExtensionMethod;

class AutonomousController {

	public:
		AutonomousController(Robot* robotPointer);
		void update();
		void startTimer();
	private:
		Timer time; 
		Robot* robot;
		void drive();
		void stop();
		bool shoot();
		bool targetReached;
};
#endif
