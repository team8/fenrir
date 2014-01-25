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
	command.getMethod().shooterState;
	free(args);
}

void Shooter::update(state){
	switch(state) {
		case IDLE:
			setAllVics(0);
			break;
		case LOADED:
			state = PREP;
			break;
		case PREP:
			// Aim the shooter and start spinning up
			setShooterVics(SHOOTER_VICS_SPEED);
			state = SHOOTING;
			break;
		case SHOOTING:
			shoot();
			state = IDLE;
		break;
	}
}

void Shooter::setShooterVics(float speed){
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
}

void Shooter::setAllVics(float speed){
	setShooterVics(speed);
	loaderVic1.set(speed);
	loaderVic2.set(speed);
}

void Shooter::shoot(){
	loaderVic1.set(LOAD_SPEED);
	loaderVic2.set(LOAD_SPEED);
}
