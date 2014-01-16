#include "Constants.h"
typedef enum {
    DRIVE
    } SubsystemType;
    
typedef enum {
    DRIVESPEED,
    DRIVEDIST,
    ROTATEANGLE,
    ROTATESPEED
    } DriveMethod;

typedef union {
    DriveArgs driveArgs;
} Args;

typedef struct {
    double value;
} DriveArgs;

class Command {
    public:
        Command(bool inAuto);
        Command(bool inAuto, SubsystemType subsystemType, int methodType, void * args);
        void command(SubsystemType subsystem, int methodEnum, void * args);
        int getSubsystem();
        int getMethod();
        bool getParent();
        void * argPointer; // Points to argument struct
    private:
        int subsystem; // Subsystem number. Defined in the commandType enum in Constants.h
        int method; // Method number. Defined in an enum in Constants.h
        bool parent; // True if autonomous, false if teleop
}
