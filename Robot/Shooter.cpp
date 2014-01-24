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

void Shooter::runCommand(RobotCommand command){
	ShooterArgs * args = (ShooterArgs *) command.argPointer;
	switch (command.getMethod().shooterMethod) {
		case SHOOT:
		break;
	}
	free(args);
}

void Shooter::update(){
	switch(state) {
		case IDLE:
			shooterVic1.Set(0);
			shooterVic2.Set(0);
			shooterVic3.Set(0);
			shooterVic4.Set(0);
			loaderVic1.Set(0);
			loaderVic2.Set(0);
			break;
		case LOADED:
			// Do we need this?
			break;
		case AIMING:
			// Aim the shooter
			break;
		case SPINNING_UP:
			shooterVic1.Set(vicsSpeed);
			shooterVic2.Set(vicsSpeed);
			shooterVic3.Set(vicsSpeed);
			shooterVic4.Set(vicsSpeed);
			break;
		case SHOOTING:
			loaderVic1.Set(vicsSpeed);
			loaderVic2.Set(vicsSpeed);
			break;
	}
}

void Shooter::shoot(float speed){
	vicsSpeed = speed;
	state = SHOOTING;
}

void Shooter::setShooterVics(float speed){
	vicsSpeed = speed;
	state = SPINNING_UP;
	
}

void Shooter::stopAllVics(){
	state = IDLE;
}
