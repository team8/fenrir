#include "Shooter.h"


Shooter::Shooter(Rangefinding *rangepointer): 
	shooterVic1(PORT_SHOOTER_VIC_1),
	shooterVic2(PORT_SHOOTER_VIC_2),
	shooterVic3(PORT_SHOOTER_VIC_3),
	shooterVic4(PORT_SHOOTER_VIC_4),
	
	loaderVic1(PORT_LOADER_VIC_1),
	loaderVic2(PORT_LOADER_VIC_2),
	
	encShooter1((uint32_t)PORT_SHOOTER_ENCODER_1A, (uint32_t)PORT_SHOOTER_ENCODER_1B, true, k4X),
	encShooter2((uint32_t)PORT_SHOOTER_ENCODER_2A, (uint32_t)PORT_SHOOTER_ENCODER_2B, true, k4X),
	encShooter3((uint32_t)PORT_SHOOTER_ENCODER_3A, (uint32_t)PORT_SHOOTER_ENCODER_3B, true, k4X),
	encShooter4((uint32_t)PORT_SHOOTER_ENCODER_4A, (uint32_t)PORT_SHOOTER_ENCODER_4B, true, k4X),
	
	encController1(0.1, 0.1, 0.1, &encShooter1, &shooterVic1),
	encController2(0.1, 0.1, 0.1, &encShooter2, &shooterVic2),
	encController3(0.1, 0.1, 0.1, &encShooter3, &shooterVic3),
	encController4(0.1, 0.1, 0.1, &encShooter4, &shooterVic4)Rangefinder
	
{
	this -> rangefinder = rangepointer;
	
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
		// case PREP:
		// 	startShooterVics(SHOOTER_VICS_SPEED);
		// 	break;
		// //named it like this because I think this sounds more like a command and helps reduce confusion
		case RobotCommand::FIRE:
			state = ALIGN;
			break;
	}
	free(args);
}

void Shooter::update(){
	//for certain cases, will not automatically switch case, waits for user
	switch(state) {
		case IDLE:
			setAllVics(0);
			// is stop a thing?
			time.Stop();
			break;
		case PREPARING:
			shooterVic1.Set(encController1.Get());
			shooterVic2.Set(encController2.Get());
			shooterVic3.Set(encController3.Get());
			shooterVic4.Set(encController4.Get());
			if(encController1.GetError()<0.01&&encController2.GetError()<0.01&&encController3.GetError()<0.01&&encController4.GetError()<0.01){
				state = FIRING;
			}
			state = FIRING;
			break;
		case ALIGN:
			Rangefinder.rotateDegrees();
			double dist =  Rangefinder.getDistance();
			while(dist != SHOOT_DISTANCE){
				void * argPointer = malloc(sizeof(DriveArgs));
				((DriveArgs*) argPointer) -> driveDist = SHOOT_DISTANCE-dist;
				RobotCommand::Method method;
				method.driveMethod = RobotCommand::DRIVEDIST;
				RobotCommand command(RobotCommand::DRIVE, method, argPointer);
				robot -> setCommand(command);
				dist = Rangefinder.getDistance();
			}
			state = PREPARING;
			break;
		case FIRING:
			
			time.Reset();
			time.Start();
			while(time.get()<=5000){
			loaderVic1.Set(LOAD_SPEED);
			loaderVic2.Set(LOAD_SPEED);
			}
	//TODO once timer reaches certain constant, switch state
			state = IDLE;
			shoot();
			// if(timer.Get()<0){
			// 	startShooterVics(SHOOTER_VICS_SPEED);
			// 	state=PREPARING;
			// }
			// else if(timer.Get()>0){
			// 	shoot();
			// }
			break;
	}
}

void Shooter::startShooterVics(float speed){
	shooterVic1.Set(speed);
	shooterVic2.Set(speed);
	shooterVic3.Set(speed);
	shooterVic4.Set(speed);
	state = PREPARING;
}

void Shooter::setAllVics(float speed){
	loaderVic1.Set(speed);
	loaderVic2.Set(speed);
}

void Shooter::shoot(){
	// time.Reset();
	// time.Start();
	loaderVic1.Set(LOAD_SPEED);
	loaderVic2.Set(LOAD_SPEED);
	//TODO once timer reaches certain constant, switch state
	state = IDLE;
}
