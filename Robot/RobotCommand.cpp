#include "Constants.h"
#include "RobotCommand.h"

RobotCommand::RobotCommand(bool inAuto) { // inAuto should be true if the Command is sent from autonomous, otherwise it is false
    parent = inAuto;
}

RobotCommand::RobotCommand(bool inAuto, SubsystemType subsystemEnum, int methodEnum, void * args) {
    subsystem = subsystemEnum;
    method = methodEnum;
    argPointer = args;
    parent = inAuto;
}

void RobotCommand::command(SubsystemType subsystemEnum, int methodEnum, void * args){ // Use one of the command type enums here
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

bool RobotCommand::getParent() {
    return parent;
}
