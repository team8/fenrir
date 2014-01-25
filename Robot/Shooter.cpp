#include "Shooter.h"

Shooter::Shooter(): 
	shooterVic1(PORT_SHOOTER_VIC_1),
	shooterVic2(PORT_SHOOTER_VIC_2),
	shooterVic3(PORT_SHOOTER_VIC_3),
	shooterVic4(PORT_SHOOTER_VIC_4),
	
	loaderVic1(PORT_LOADER_VIC_1),
	loaderVic2(PORT_LOADER_VIC_2),
	
	encShooter((uint32_t)PORT_SHOOTER_ENCODER_1A, (uint32_t)PORT_SHOOTER_ENCODER_1B)
{
}

void Shooter::runCommand(RobotCommand command){
	ShooterArgs* args = (ShooterArgs*) command.argPointer;
	switch(command.getMethod().shooterMethod) {
		case PREP:
			setShooterVics(SHOOTER_VICS_SPEED);
			break;
		case FIRING:
			shoot();
			break;
	}
	free(args);
}

void Shooter::update(){
	//for certain cases, will not automatically switch case, waits for user
	switch(state) {
		case NOT_SHOOTING:
			setAllVics(0);
			break;
		case CHECK_LOADED:
			//do something to check if there is a ball, then if true, start prepping 
			if(true)state = PREP;
			break;
		case PREP:
			getShooterEncs(float encSpeed);
			if(encSpeed>0){//minimum speed needed for shooting
			state=FIRING;
			}
			break;
		case FIRING:
			shoot();
		break;
	}
}

void Shooter::setShooterVics(float speed){
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
}

void Shooter::getShooterEncs(float encSpeed){
	encSpeed = encShooter.Get();
}
void Shooter::setAllVics(float speed){
	setShooterVics(speed);
	loaderVic1.Set(speed);
	loaderVic2.Set(speed);
}

void Shooter::shoot(){
	time.Reset();
	time.Start();
	loaderVic1.Set(LOAD_SPEED);
	loaderVic2.Set(LOAD_SPEED);
	state = NOT_SHOOTING;
}
