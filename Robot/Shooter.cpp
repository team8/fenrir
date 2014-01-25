#include "Shooter.h"

Shooter::Shooter(): 
	shooterVic1(PORT_SHOOTER_VIC_1),
	shooterVic2(PORT_SHOOTER_VIC_2),
	shooterVic3(PORT_SHOOTER_VIC_3),
	shooterVic4(PORT_SHOOTER_VIC_4),
	
	loaderVic1(PORT_LOADER_VIC_1),
	loaderVic2(PORT_LOADER_VIC_2),
	
	encShooter1((uint32_t)PORT_SHOOTER_ENCODER_1A, (uint32_t)PORT_SHOOTER_ENCODER_1B),
	encShooter2((uint32_t)PORT_SHOOTER_ENCODER_2A, (uint32_t)PORT_SHOOTER_ENCODER_2B),
	encShooter3((uint32_t)PORT_SHOOTER_ENCODER_3A, (uint32_t)PORT_SHOOTER_ENCODER_3B),
	encShooter4((uint32_t)PORT_SHOOTER_ENCODER_4A, (uint32_t)PORT_SHOOTER_ENCODER_4B),
	
	encController1(0.1, 0.1, 0.1, &encShooter1, &shooterVic1),
	encController2(0.1, 0.1, 0.1, &encShooter2, &shooterVic2),
	encController3(0.1, 0.1, 0.1, &encShooter3, &shooterVic3),
	encController4(0.1, 0.1, 0.1, &encShooter4, &shooterVic4)
{
	encShooter1.Start();
	encShooter2.Start();
	encShooter3.Start();
	encShooter4.Start();
	
	encController1.SetOutputRange(-1,1);
	encController2.SetOutputRange(-1,1);
	encController3.SetOutputRange(-1,1);
	encController4.SetOutputRange(-1,1);
}

void Shooter::runCommand(RobotCommand command){
	ShooterArgs* args = (ShooterArgs*) command.argPointer;
	switch(command.getMethod().shooterMethod) {
		case PREPARING_TO_SHOOT:
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
			if(true)state = PREPARING_TO_SHOOT;
			break;
		case PREPARING_TO_SHOOT:
			//aim
			shooterVic1.Set(encController1.Get());
			shooterVic2.Set(encController2.Get());
			shooterVic3.Set(encController3.Get());
			shooterVic4.Set(encController4.Get());
			//if statement to check if ready to shoot
			state=FIRING;
			
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
