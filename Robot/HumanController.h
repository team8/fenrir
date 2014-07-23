#ifndef HUMANCONTROLLER_H
#define HUMANCONTROLLER_H
#include "Constants.h"
#include "Robot.h"
#include "RobotCommand.h"
#include "XBoxController.h"
#include <WPILib.h>
#include <stdlib.h>

class HumanController {
public:
	HumanController(Robot *robotPointer);
	void update();

private:
	Robot *robot;
#ifdef JOYSTICK_CONTROLS	
	Joystick speedStick;
	Joystick turnStick;
	Joystick operatorStick;
	//bool lastFlushTrigger;
	//bool prevRangeButton;
	bool shootButtonPrev;
	bool getShootButton();
	bool getFlushTrigger();
	double getOperatorZ();
	bool getRangeButton();
	double getAccumulatorStick();
#elif defined XBOX_CONTROLS
	XBoxController xbox;
	int shootButtonPrev;
	int getShootButton();
	bool getWarmupButton();
#endif
	double getSpeedStick();
	double getTurnStick();

	//booleans used to make sure we don't reissue same command;
	bool prevStop;
	bool prevShoot;
};
#endif
