#include "Shooter.h"

Shooter::Shooter() :
			shooterVic1((uint32_t) PORT_SHOOTER_VIC_1),
			shooterVic2((uint32_t) PORT_SHOOTER_VIC_2),
			shooterVic3((uint32_t) PORT_SHOOTER_VIC_3),
			shooterVic4((uint32_t) PORT_SHOOTER_VIC_4),

			loaderVic((uint32_t) PORT_LOADER_VIC),

			encShooter1((uint32_t) PORT_SHOOTER_ENCODER_1A, (uint32_t) PORT_SHOOTER_ENCODER_1B, true),
			encShooter2((uint32_t) PORT_SHOOTER_ENCODER_2A, (uint32_t) PORT_SHOOTER_ENCODER_2B, true),
			encShooter3((uint32_t) PORT_SHOOTER_ENCODER_3A, (uint32_t) PORT_SHOOTER_ENCODER_3B, true),
			encShooter4((uint32_t) PORT_SHOOTER_ENCODER_4A, (uint32_t) PORT_SHOOTER_ENCODER_4B, true),

			encController1(0.1, 0.1, 0.1, &encShooter1, &shooterVic1),
			encController2(0.1, 0.1, 0.1, &encShooter2, &shooterVic2),
			encController3(0.1, 0.1, 0.1, &encShooter3, &shooterVic3),
			encController4(0.1, 0.1, 0.1, &encShooter4, &shooterVic4)

{
	std::printf("Shooter constructor\n");

	isShooting = false;
	encShooter1.Start();
	encShooter2.Start();
	encShooter3.Start();
	encShooter4.Start();

	encController1.SetOutputRange(-1, 1);
	encController2.SetOutputRange(-1, 1);
	encController3.SetOutputRange(-1, 1);
	encController4.SetOutputRange(-1, 1);
}

void Shooter::runCommand(RobotCommand command) {
	ShooterArgs* args = (ShooterArgs*) command.argPointer;
	switch (command.getMethod().shooterMethod) {
	case RobotCommand::MANUAL_LOAD:
		state = M_LOAD;
		break;
	case RobotCommand::MANUAL_FIRE:
		state = M_FIRE;
		break;
	case RobotCommand::FIRE:
		shootTimer.Reset();
		shootTimer.Start();
		state = PREPARING;
		break;
	case RobotCommand::EJECT:
		if(state !=PREPARING && state !=FIRING)state = EJECT;
		break;
	case RobotCommand::IDLE:
		if(state !=PREPARING && state !=FIRING)state = IDLE;
		break;
	case RobotCommand::FLUSH:
		if(state !=PREPARING && state !=FIRING)state = FLUSH;
		break;
	}
	free(args);
}

void Shooter::update() {
	//for certain cases, will not automatically switch case, waits for timer
	switch (state) {
	// M FOR MANUAL
	case M_FIRE:
		startShooterVics(1.0);
		break;
	case M_LOAD:
		loaderVic.Set(LOAD_SPEED);
		break;
	case IDLE:
		setAllVics(0);
		break;
		//Prepares AND Aligns simultaneously
	case PREPARING:
		if (!shootTimer.HasPeriodPassed(3.0)) {
			startShooterVics(1.0);
		}
		else {
			std::printf("fire\n");
			state = FIRING;
			shootTimer.Reset();
		}
		break;
	case FIRING:
		if (!shootTimer.HasPeriodPassed(3.0)) {
			loaderVic.Set(LOAD_SPEED);
		}
		else {
			state = IDLE;
		}
		break;
	case EJECT:
		eject();
		break;
	case FLUSH:
		setAllVics(-.85);
		break;
	}
}

void Shooter::startShooterVics(double speed) {
	shooterVic1.Set(-speed);
	shooterVic2.Set(-speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
}

void Shooter::setAllVics(double speed) {
	shooterVic1.Set(-speed);
	shooterVic2.Set(-speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
	loaderVic.Set(-speed);
}

void Shooter::eject() {
	loaderVic.Set(1);
}
