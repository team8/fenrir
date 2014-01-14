#include "Constants.h"
#include "Command.h"

Command::Command() {
    
}

Command::Command(int subsystemEnum, int methodEnum, int newPassValue) {
    subsystem = subsystemEnum;
    method = methodEnum;
    passValue = newPassValue;
}

void command(int subsystemEnum, int methodEnum, int newPassValue){ // Use one of the command type enums here
    subsystem = subsystemEnum;
    method = methodEnum;
    passValue = newPassValue;
}

int getSubsystem() {
    return subsystem;
}

int getMethod() {
    return method;
}

int getPassValue() {
    return passValue;
}
