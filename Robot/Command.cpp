#include "Constants.h"

class Command {
    private:
        void drive();
        void shoot();
    public:
        Command();
        void command(int);

};
Command::Command() {
    command(DRIVE);
}

void drive() {
    // Do driving stuff here
}

void shoot() {
    // Do shooting stuff here
}

void command(int type){ // Use one of the command type enums here
    if (type == DRIVE) {
        drive();
    } else if (type == SHOOT) {
        shoot();
    }
}
