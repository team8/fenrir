Fenrir
==

The big bad wolf, son of Loki. Chosen because wolves live in packs (teams) and exemplify the values of cohesiveness, tenacity, and winning everything. :clap:

Structure of Code:

Fenrir.cpp is where all the states of the Robot are interpreted (Teleop Init, Disabled...). It calls methods from Robot(.cpp/.h)...

Robot(.cpp/.h) has the init(), disable(), update(), and command creating/running methods. It calls update() on each subsystem of the robot to have them each run simultaneously after it initializes them. The commands it can create/run come from...

RobotCommand(.h mostly). RobotCommand has all the enums and structs that name all the states and methods the various subsystems can run/be in. It uses pointers to pass any arguments needed for each subsystem, and is basically the number 1 thing needed to keep our program modular. These commands are created by...

AutonomousController and HumanController. AutonomousController issues commands in a particular order based on time, and is hard-coded in what it will do. HumanController issues commands according to Joystick input that we receive from the drivers(humans). Thanks to the command class, these controllers are able to issue commands to various subsytems without having to directly access the methods of each subsystem, allowing us to minimize the number of global variables/methods and to keep the code modular. These commands are then run by...

Accumulator, which is our subsytem for picking up(accumulating) the ball, and for passing it.

DriveTrain, which turns our otherwise-would-be primitive sessile object into an awesome ...non-sessile object :thumbsup:

Rangefinder, which we are supposed to use(:open_mouth:) to try to make our shooter and autonomous more precise by aligning the robot and moving to appropriate distances

Robot, which is technically a subsytem of itself :thumbsup:

Shooter, which we use to shoot the ball :anguished:

Finally, Constants.h is where we store almost all of our constants(excludes our debug ones) including but not limited to, port numbers, default victor(speed controller) speeds, and joystick button/trigger numbers.
