#include "Constants.h"
#include "Command.h"

Command::Command() {
    
}

Command::Command(int subsystemEnum, int methodEnum, void * args) {
    subsystem = subsystemEnum;
    method = methodEnum;
    argPointer = args;
}

void command(int subsystemEnum, int methodEnum, void * args){ // Use one of the command type enums here
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
