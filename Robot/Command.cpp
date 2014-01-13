class Command {
    public:
    Command();
};

Command::Command() {
    
    enum commandType{DRIVE, SHOOT};
    
}

void command(int type){ // Use one of the command type enums here
    if (type == DRIVE) {
        drive();
    }
}

void drive() {
    
}
