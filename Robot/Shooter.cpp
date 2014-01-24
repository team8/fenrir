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
void Shooter::shoot(){
        loaderVic1.set(LOAD_SPEED);
        loaderVic2.set(LOAD_SPEED);
}

void Shooter::update(){
        switch(state) {
                case IDLE:
                        setAllVics(0);
                        break;
                case LOADED:
                        // Do we need this?
                        break;
                case AIMING:
                        // Aim the shooter
                        break;
                case SPINNING_UP:
                        setShooterVics(SHOOTER_TOP_SPEED);
                        break;
                case SHOOTING:
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
        setShooterVics(0);
        loaderVic1.set(0);
        loaderVic2.set(0);
}
