using namespace std;

enum commandType{DRIVE, SHOOT};
 
void drive();
void shoot();

void command(int type){ // Use one of the command type enums here
    if (type == DRIVE) {
        drive();
    } else if (type == SHOOT) {
        shoot();
    }
}

void drive() {
    // Do driving stuff
}

void shoot() {
    // Do shooting stuff
}
