#include "Shooter.h"

Shooter::Shooter(): 
  
	shooterVic1(PORT_SHOOTER_VIC_1),
	shooterVic2(PORT_SHOOTER_VIC_2),
	shooterVic3(PORT_SHOOTER_VIC_3),
	shooterVic4(PORT_SHOOTER_VIC_4),

	loaderVic1(PORT_LOADER_VIC_1),
	loaderVic2(PORT_LOADER_VIC_2)
{

}

void Shooter::shoot(){
  
}

void Shooter::update(){
	switch(state) {
		case IDLE:
			setAllVics(setVicsSpeed);
			break;
		case LOADED:
			// Do we need this?
			break;
		case AIMING:
			// Aim the shooter
			break;
		case SPINNING_UP:
			shooterVic1.Set(setVicsSpeed);
			shooterVic2.Set(setVicsSpeed);
			shooterVic3.Set(setVicsSpeed);
			shooterVic4.Set(setVicsSpeed);
			break;
		case SHOOTING:
			// Do something
			break;
	}
}

void Shooter::setAllVics(float speed){
	state = SPINNING_UP;
	setVicsSpeed = speed;
}

void Shooter::runCommand(RobotCommand command){
	ShooterArgs * args = (ShooterArgs *) command.argPointer;
	switch (command.getMethod().shooterMethod) {
		case SHOOT:   
			break;
	}
	free(args);
}
