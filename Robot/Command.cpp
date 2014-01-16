#include "Constants.h"
#include "Command.h"

Command::Command(bool inAuto) { // inAuto should be true if the Command is sent from autonomous, otherwise it is false
    parent = inAuto;
}

Command::Command(bool inAuto, SubsystemType subsystemEnum, int methodEnum, void * args) {
    subsystem = subsystemEnum;
    method = methodEnum;
    argPointer = args;
    parent = inAuto;
}

void command(SubsystemType subsystemEnum, int methodEnum, void * args){ // Use one of the command type enums here
    subsystem = subsystemEnum;
    method = methodEnum;
    argPointer = args;
}

int getSubsystem() {
    return subsystem;
}

int getMethod() {
    return method;
}

bool getParent() {
    return parent;
}
