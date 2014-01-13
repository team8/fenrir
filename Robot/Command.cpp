#include "Constants.h"
#include "Command.h"

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
