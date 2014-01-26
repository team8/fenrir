#include "Constants.h"
#include "RobotCommand.h"

	RobotCommand::RobotCommand(SubsystemType subsystemType, Method methodType, void * args){
		// Use one of the command type enums here
    subsystem = subsystemType;
    method = methodType;
    argPointer = args;
}

SubsystemType RobotCommand::getSubsystem() {
    return subsystem;
}

Method RobotCommand::getMethod() {
    return method;
}

