//ports for HumanController
#define PORT_SPEED 1
#define PORT_TURN 2
#define PORT_OPERATOR 3

//Helps refine sensitivity of joystiks
#define SPEED_SENSITIVITY 0.5
#define ROTATE_SENSITIVITY
//ports for drive train victors
#define PORT_DRIVE_VIC_1 0
#define PORT_DRIVE_VIC_2 1
#define PORT_DRIVE_VIC_3 0
#define PORT_DRIVE_VIC_4 2

//ports for drive train encoders
#define PORT_ENCODER_RIGHT_A 1
#define PORT_ENCODER_RIGHT_B 7
#define PORT_ENCODER_LEFT_A 12
#define PORT_ENCODER_LEFT_B 13
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
#define PORT_SHOOTER_VIC_1 0
#define PORT_SHOOTER_VIC_2 0
#define PORT_SHOOTER_VIC_3 6
#define PORT_SHOOTER_VIC_4 7
#define PORT_LOADER_VIC_1 4
#define PORT_LOADER_VIC_2 5

//default speed for loaders 
#define LOAD_SPEED .5

//ports for accumulator victors
//#define PORT_ACCUMULATOR_VIC_5 0
//#define PORT_ACCUMULATOR_VIC_6 0
#define PORT_ACCUMULATOR_VIC_7 3

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
#define ACCUMULATOR_BUTTON_PORT 3
#define WARMUP_BUTTON_PORT 0
#define PASS_BUTTON_PORT 2


// Ultrasonic ports
#define ULTRASONIC_ECHO_PULSE_OUTPUT_1 0 // Left
#define ULTRASONIC_TRIGGER_PULSE_INPUT_1 0
#define ULTRASONIC_ECHO_PULSE_OUTPUT_2 0 // Right
#define ULTRASONIC_TRIGGER_PULSE_INPUT_2 0
#define ULTRA_GAP 1 // Distance between the two ultrasonic sensors in inches, 1 to avoid division by 0

#define SHOOT_DISTANCE 0 //The set distance we want it to shoot at
