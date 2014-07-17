
/***########*******Only one of these should be defined at a time*******#######***/
//#define JOYSTICK_CONTROLS
#ifndef JOYSTICK_CONTROLS
#define XBOX_CONTROLS
#endif

/*Joystick and XBox Ports*/
#if defined JOYSTICK_CONTROLS
#define PORT_SPEED 1
#define PORT_TURN 2
#define PORT_OPERATOR 3
#elif defined XBOX_CONTROLS
#define PORT_XBOX 1
#endif


//Helps refine sensitivity of joystiks
#define SPEED_SENSITIVITY 0.5
#define ROTATE_SENSITIVITY
//ports for drive train victors
#define PORT_DRIVE_VIC_LEFT_FRONT 5
#define PORT_DRIVE_VIC_LEFT_BACK 6
#define PORT_DRIVE_VIC_RIGHT_FRONT 1
#define PORT_DRIVE_VIC_RIGHT_BACK 2

//ports for drive train encoders
#define PORT_ENCODER_RIGHT_A 1
#define PORT_ENCODER_RIGHT_B 2
#define PORT_ENCODER_LEFT_A 5
#define PORT_ENCODER_LEFT_B 6
#define DISTANCE_PER_ROT 6*atan(1)*4 //6 pi for prototype
//ports for drive train gyroscopes
#define PORT_GYRO 0

//default speeds for DriveTrain
#define DEFAULT_AUTO_ROTATE 0.5

//ports for vision


//ports for shooter encoders
#define PORT_SHOOTER_ENCODER_1 0
#define PORT_SHOOTER_ENCODER_2 0
#define PORT_SHOOTER_ENCODER_3 0
#define PORT_SHOOTER_ENCODER_4 0

//ports for shooter victors
#define PORT_SHOOTER_VIC_1 3
#define PORT_SHOOTER_VIC_2 4
#define PORT_SHOOTER_VIC_3 8
#define PORT_SHOOTER_VIC_4 7 //this one (previously 7)
#define PORT_LOADER_VIC 9

//default speed for loaders 
#define LOAD_SPEED -1

//ports for accumulator victors
//#define PORT_ACCUMULATOR_VIC_5 0
//#define PORT_ACCUMULATOR_VIC_6 0
#define PORT_ACCUMULATOR_VIC_7 10

//ports for accumulator encoders
#define PORT_ACCUMULATOR_ENC_1A 0
#define PORT_ACCUMULATOR_ENC_1B 0
#define PORT_ACCUMULATOR_ENC_2A 0
#define PORT_ACCUMULATOR_ENC_2B 0

//default distances for accumulator deploy and retract

#define DEFAULT_DEPLOY_DIST 1
#define DEFAULT_RETRACT_DIST -1

//Constants for the Vics for shooting
#define SHOOTER_VICS_SPEED 1

//Encoder Ports
#define PORT_SHOOTER_ENCODER_1A 0//is this obselete with the other shooter encoders?
#define PORT_SHOOTER_ENCODER_1B 0
#define PORT_SHOOTER_ENCODER_2A 0
#define PORT_SHOOTER_ENCODER_2B 0
#define PORT_SHOOTER_ENCODER_3A 0
#define PORT_SHOOTER_ENCODER_3B 0
#define PORT_SHOOTER_ENCODER_4A 0
#define PORT_SHOOTER_ENCODER_4B 0

//button number for operator stick trigger
#define ACCUMULATOR_BUTTON_PORT 10
#define FLUSH_TRIGGER 2

// Ultrasonic ports
#define ULTRASONIC_CHANNEL_LEFT 1
#define ULTRASONIC_RX_LEFT 13
#define ULTRASONIC_CHANNEL_RIGHT 2
#define ULTRASONIC_RX_RIGHT 14
#define HIGH 1
#define LOW 0
#define ULTRA_GAP 1 // Distance between the two ultrasonic sensors in inches


#define SHOOT_DISTANCE 0 //The set distance we want it to shoot at
