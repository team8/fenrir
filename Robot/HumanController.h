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
	HumanController(Robot *robotPointer);

private:
	Robot *robot;
	Joystick speedStick;
	Joystick turnStick;
	Joystick operatorStick;

	//All methods we use in controller scheme logic
	double getSpeedStick();
	double getTurnStick();
	double getAccumulatorStick();
	double getAccumulator();
	bool getShootButton();
	bool getWarmupButton();
	bool getFlushTrigger();
	double getOperatorZ();
	bool getRangeButton();

	//booleans used to make sure we don't reissue same command
	bool accuButtonPrev;
	bool shootButtonPrev;
	bool warmupButtonPrev;
	bool passButtonPrev;
	bool lastFlushTrigger;
	bool prevRangeButton;
	bool prevStop;
	bool prevZ;
};
#endif
