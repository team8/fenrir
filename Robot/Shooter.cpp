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
		shootTimer.Reset();
		shootTimer.Start();
		std::printf("This is working\n");
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
		break;
		//Prepares AND Aligns simultaneously
	case PREPARING:
		std::printf("Current Time: %f \n", shootTimer.Get());
		break;
		if(!shootTimer.HasPeriodPassed(1.0)) {
			startShooterVics(0.5);
			std::printf("%f \n", shootTimer.Get());
		}
		else /*if (aligned == true)*/{
			std::printf("Firing\n");
			std::printf("%f \n", shootTimer.Get());
			state = FIRING;
		}
		break;

	case FIRING:
		if(!shootTimer.HasPeriodPassed(6.0)){
			loaderVic1.Set(LOAD_SPEED);
			loaderVic2.Set(LOAD_SPEED);
		}
		else {
			//std::printf("Idling\n");
			state = IDLE;
		}
		break;
	}
}

void Shooter::startShooterVics(double speed) {
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
}

void Shooter::setAllVics(double speed) {
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
	loaderVic1.Set(speed);
	loaderVic2.Set(speed);
}
