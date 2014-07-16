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
#if defined JOYSTICK_CONTROLS	
	Joystick speedStick;
	Joystick turnStick;
	Joystick operatorStick;
#elif defined XBOX_CONTROLS
	XBoxController xbox;
#endif

	double getSpeedStick();
	double getTurnStick();
	double getAccumulatorStick();
	double getAccumulator();
#if defined JOYSTICK_CONTROLS
	bool getShootButton();
#elif defined XBOX_CONTROLS
	int getShootButton();
#endif
	bool getWarmupButton();
#ifdef JOYSTICK_CONTROLS
	bool getFlushTrigger();
	double getOperatorZ();
	bool getRangeButton();
#endif
	//booleans used to make sure we don't reissue same command
	bool accuButtonPrev;
#if defined JOYSTICK_CONTROLS
	bool shootButtonPrev;
#elif defined XBOX_CONTROLS
	int shootButtonPrev;
#endif
	bool warmupButtonPrev;
	bool passButtonPrev;
#ifdef JOYSTICK_CONTROLS
	bool lastFlushTrigger;
	bool prevRangeButton;
#endif
	bool prevStop;
	bool prevShoot;
};
#endif
