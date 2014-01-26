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
		case PREP:
			startShooterVics(SHOOTER_VICS_SPEED);
			break;
		//named it like this because I think this sounds more like a command and helps reduce confusion
		case FIRE:
			//once trigger is pulled, shoots
			//fire(/*Pointer to the trigger*/args->trigger); undefined function, suposedly not needed
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
/*		case CHECK_LOADED: //isn't this redundant??
			//do something to check if there is a ball, then if true, start prepping 
			if(true)state = PREP;
			break; */
		case PREPARING_TO_SHOOT:
			shooterVic1.Set(encController1.Get());
			shooterVic2.Set(encController2.Get());
			shooterVic3.Set(encController3.Get());
			shooterVic4.Set(encController4.Get());
			if(encController1.GetError()<0.01&&encController2.GetError()<0.01&&encController3.GetError()<0.01&&encController4.GetError()<0.01){
				timer.Start();
			}
		state = FIRING;
			break;
		case FIRING:
			if(timer.Get()<0){
				startShooterVics(SHOOTER_VICS_SPEED);
				state=PREPARING_TO_SHOOT;
			}
			else if(timer.Get()>0){
				shoot();
			}
			break;
	}
}

void Shooter::startShooterVics(float speed){
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
	state = PREPARING_TO_SHOOT;
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
	//TODO once timer reaches certain constant, switch state
	state = NOT_SHOOTING;
}
