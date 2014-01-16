//ports for HumanController
#define PORT_SPEED 0;
#define PORT_OPERATOR 0;
#define PORT_TURN 0;

//ports for drive train victors
#define PORT_DRIVE_VIC_1 0;
#define PORT_DRIVE_VIC_2 0;
#define PORT_DRIVE_VIC_3 0;
#define PORT_DRIVE_VIC_4 0;

//ports for drive train encoders
#define PORT_ENCODER_RIGHT 0;
#define PORT_ENCODER_LEFT 0;

//ports for vision
#define  //add more stuff later


//ports for shooter encoders
#define PORT_SHOOTER_ENCODER_1 0
#define PORT_SHOOTER_ENCODER_2 0
#define PORT_SHOOTER_ENCODER_3 0
#define PORT_SHOOTER_ENCODER_4 0

//ports for shooter victors
#define PORT_SHOOTER_VIC_1 0
#define PORT_SHOOTER_VIC_2 0
#define PORT_SHOOTER_VIC_3 0
#define PORT_SHOOTER_VIC_4 0

enum ShooterState {EMTPY, LOADED, WARMUP, AIMING, SHOOTING, RECOVERING};
