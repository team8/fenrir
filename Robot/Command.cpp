#include "Constants.h"

class Command {
    public:
        Command();
        Command(int subsystemEnum, int methodEnum, int newPassValue);
        void command(int subsystemEnum, int methodEnum, int newPassValue);
        int[] getCommand();
        int getSubsystem();
        int getMethod();
        int getPassValue();
    private:
        int subsystem; // Subsystem number. Defined in the commandType enum in Constants.h
        int method; // Method number. Defined in an enum in Constants.h
        int passValue; // Value passed to the method
        int values [3];
};

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

int[] getCommand() {
    values = {subsystem, method, passValue};
    return values;
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
