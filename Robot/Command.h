typedef enum {
    DRIVE
    } CommandType;
    
typedef enum {
    DRIVESPEED,
    DRIVEDIST,
    ROTATEANGLE,
    ROTATESPEED
    } DriveMethod;

typedef struct {
    double value;
} DriveArgs;

class Command {
    public:
        Command();
        Command(CommandType subsystemType, int methodType, void * args);
        void command(int subsystemEnum, int methodEnum, void * args);
        int getSubsystem();
        int getMethod();
        void * argPointer; // Points to argument struct
    private:
        int subsystem; // Subsystem number. Defined in the commandType enum in Constants.h
        int method; // Method number. Defined in an enum in Constants.h
}
