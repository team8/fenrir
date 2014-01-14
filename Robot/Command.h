enum commandType{DRIVE};
enum driveMethod{SETSPEED, DRIVEDIST, ROTATEANGLE, ROTATESPEED};

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
