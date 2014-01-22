#include "Shooter.h"

Shooter::Shooter(): 
  
	shooterVic1(PORT_SHOOTER_VIC_1),
	shooterVic2(PORT_SHOOTER_VIC_2),
	shooterVic3(PORT_SHOOTER_VIC_3),
	shooterVic4(PORT_SHOOTER_VIC_4)
{

}

void Shooter::shoot(){
  
}

void Shooter::update(){
	switch(state) {
		case SHOOTER_IDLE:
			shooterVic1.Set(0);
			shooterVic2.Set(0);
			shooterVic3.Set(0);
			shooterVic4.Set(0);
			break;
		case LOADED:
			// Do we need this?
			break;
		case AIMING:
			// Aim the shooter
			break;
		case SPINNING_UP:
			// Spin the wheels up to speed
			break;
		case SHOOTING:
			// Do something
			break;
	}
}

void Shooter::runCommand(RobotCommand command){
	ShooterArgs * args = (ShooterArgs *) command.argPointer;
	switch (command.getMethod().shooterMethod) {
		case SHOOT:
			break;
	}
	free(args);
}
