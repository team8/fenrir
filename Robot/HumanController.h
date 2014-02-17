#ifndef HUMANCONTROLLER_H
#define HUMANCONTROLLER_H
#include "Constants.h"
#include "Robot.h"
#include "RobotCommand.h"
#include <WPILib.h>
#include <stdlib.h>

class HumanController {

	public:
		void update();
		double getSpeedStick();
		double getTurnStick();
		double getAccumulatorStick();
		double getAccumulator();
		bool getShootButton();
		bool getWarmupButton();
		
		HumanController(Robot *robotPointer);

	private:
		Robot *robot;
		Joystick speedStick;
		Joystick turnStick;
		Joystick operatorStick;
		bool accuButtonPrev;
		bool shootButtonPrev;
		bool warmupButtonPrev;
		bool passButtonPrev;
		bool autoTester;
};
#endif
