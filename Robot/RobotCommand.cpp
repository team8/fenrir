#include "Constants.h"
#include "RobotCommand.h"

	RobotCommand::RobotCommand(SubsystemType subsystemEnum, int methodEnum, void * args){ // Use one of the command type enums here
    subsystem = subsystemEnum;
    method = methodEnum;
    argPointer = args;
}

SubsystemType RobotCommand::getSubsystem() {
    return subsystem;
}

int RobotCommand::getMethod() {
    return method;
}
