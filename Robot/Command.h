enum CommandType{DRIVE};
enum DriveMethod{DRIVESPEED, DRIVEDIST, ROTATEANGLE, ROTATESPEED};

typedef struct {
    double value;
} DriveArgs;

class Command {
    public:
        Command();
        Command(int subsystemEnum, int methodEnum, void * args);
        void command(int subsystemEnum, int methodEnum, void * args);
        int getSubsystem();
        int getMethod();
        void * argPointer; // Points to argument struct
    private:
        int subsystem; // Subsystem number. Defined in the commandType enum in Constants.h
        int method; // Method number. Defined in an enum in Constants.h
}
