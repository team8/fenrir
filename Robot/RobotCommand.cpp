#include "Constants.h"
#include "RobotCommand.h"

	RobotCommand::RobotCommand(SubsystemType subsystemType, Method methodType, void * args) {
	
	// Use one of the command type enums here
	subsystem = subsystemType;
	method = methodType;
	argPointer = args;
}

RobotCommand::SubsystemType RobotCommand::getSubsystem() {
	return subsystem;
}

RobotCommand::Method RobotCommand::getMethod() {
	return method;
}

