#include "Shooter.h"


Shooter::Shooter(): 
shooterVic1((uint32_t)PORT_SHOOTER_VIC_1),
shooterVic2((uint32_t)PORT_SHOOTER_VIC_2),
shooterVic3((uint32_t)PORT_SHOOTER_VIC_3),
shooterVic4((uint32_t)PORT_SHOOTER_VIC_4),

loaderVic1((uint32_t)PORT_LOADER_VIC_1),
loaderVic2((uint32_t)PORT_LOADER_VIC_2),

encShooter1((uint32_t)PORT_SHOOTER_ENCODER_1A, (uint32_t)PORT_SHOOTER_ENCODER_1B, true),
encShooter2((uint32_t)PORT_SHOOTER_ENCODER_2A, (uint32_t)PORT_SHOOTER_ENCODER_2B, true),
encShooter3((uint32_t)PORT_SHOOTER_ENCODER_3A, (uint32_t)PORT_SHOOTER_ENCODER_3B, true),
encShooter4((uint32_t)PORT_SHOOTER_ENCODER_4A, (uint32_t)PORT_SHOOTER_ENCODER_4B, true),

encController1(0.1, 0.1, 0.1, &encShooter1, &shooterVic1),
encController2(0.1, 0.1, 0.1, &encShooter2, &shooterVic2),
encController3(0.1, 0.1, 0.1, &encShooter3, &shooterVic3),
encController4(0.1, 0.1, 0.1, &encShooter4, &shooterVic4)

{
	time.Start();
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
	case RobotCommand::FIRE:
		time.Reset();
		state = PREPARING;
		break;
	}
	free(args);
}

void Shooter::update(){
	//for certain cases, will not automatically switch case, waits for timer
	switch(state) {
	case IDLE:
		setAllVics(0);
		time.Stop();
		break;
		//Prepares AND Aligns simultaneously
	case PREPARING:
		prepare();
		break;

	case FIRING:
		while(time.Get()<=5000){
			loaderVic1.Set(LOAD_SPEED);
			loaderVic2.Set(LOAD_SPEED);
		}
		//TODO once timer reaches certain constant, switch state
		state = IDLE;
		if(timer.Get()<0){
			startShooterVics(SHOOTER_VICS_SPEED);
			state=PREPARING;
		}
		else if(timer.Get()>0){
			shoot();
		}
		break;
	}
}

void Shooter::startShooterVics(float speed) {
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
}

void Shooter::setAllVics(float speed) {
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
	loaderVic1.Set(speed);
	loaderVic2.Set(speed);
}

void Shooter::prepare(float speed) {
	//align using rangefinders and drive train
	
	if(time.Get()<=5000) {
		startShooterVics(0.5);
	}
	else if(aligned==true) {
		time.Reset();
		state = FIRING;
	}
}

void Shooter::shoot(){
	loaderVic1.Set(loadSpeed);
	loaderVic2.Set(loadSpeed);
	//TODO once timer reaches certain constant, switch state
	state = IDLE;
}
