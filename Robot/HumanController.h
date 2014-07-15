#ifndef HUMANCONTROLLER_H
#define HUMANCONTROLLER_H
#include "Constants.h"
#include "Robot.h"
#include "RobotCommand.h"
#include "XBoxController.h"
#include <WPILib.h>
#include <stdlib.h>

/***########*******Only one of these should be defined at a time*******#######***/
//#define JOYSTICK_CONTROLS 
#define XBOX_CONTROLS

class HumanController {
public:
	void update();
	HumanController(Robot *robotPointer);

private:
	Robot *robot;
#if defined JOYSTICK_CONTROLS	
	Joystick speedStick;
	Joystick turnStick;
	Joystick operatorStick;
#elif defined XBOX_CONTROLS
	XBoxController xbox;
#endif
	

	//All methods we use in controller scheme logic
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
	bool getFlushTrigger();
	double getOperatorZ();
	bool getRangeButton();

	//booleans used to make sure we don't reissue same command
	bool accuButtonPrev;
#if defined JOYSTICK_CONTROLS
	bool shootButtonPrev;
#elif defined XBOX_CONTROLS
	int shootButtonPrev;
#endif
	bool warmupButtonPrev;
	bool passButtonPrev;
	bool lastFlushTrigger;
	bool prevRangeButton;
	bool prevStop;
	bool prevShoot;
};
#endif
