#include "Constants.h"

class Command {
    public:
        Command();
        Command(int, int);
        void command(int);
        int[] getCommand();
    private:
        int subsystem;
        int method;
        int values [2];
};

Command::Command() {
    
}

Command::Command(int subsystemEnum, int methodEnum) {
    subsystem = subsystemEnum;
    method = methodEnum;
}

void command(int subsystemEnum, int methodEnum){ // Use one of the command type enums here
    subsystem = subsystemEnum;
    method = methodEnum;
}

int[] getCommand() {
    values = {subsystem, method};
    return values;
}
