#ifndef RANGEFINDING_H
#define RANGEFINDING_H
#include <WPILib.h>
#include <stdlib.h>
#include "RobotCommand.h"
#include "Drivetrain.h"
#include "Robot.h"
#include "Constants.h"

Ultrasonic ultraLeft(ECHO_PULSE_OUT_1, TRIGGER_PULSE_IN_1);
Ultrasonic ultraRight(ECHO_PULSE_OUT_2, TRIGGER_PULSE_IN_2);

void rotateDegrees(Robot* robot) { // Returns the amount of degrees of rotation needed to be perpendicular to the wall
        ultraLeft.Ping(); // Sends ping
        if (ultraLeft.IsRangeValid()) {
                int leftDist = ultraLeft.GetRangeInches();
                ultraRight.Ping();
                if (ultraRight.IsRangeValid()) {
                        int rightDist = ultraRight.GetRangeInches();
                        double angle = atan((leftDist - rightDist)/ULTRA_GAP);
                        
                        // Sends Command
                        void * argPointer = malloc(sizeof(DriveArgs));
                        ((DriveArgs*) argPointer) -> rotAngle = angle;
                        Method method;
                        method.driveMethod = ROTATEANGLE;
                        Command command(DRIVE, method, argPointer);
                        robot -> setCommand(command);
                        return;
                }
                printf("Right Ultrasonic - Invalid range\n");
                return;
        }
        printf("Left Ultrasonic - Invalid range\n");
}
#endif

double getDistance() {
        ultraLeft.Ping();
        int leftDist = ultraLeft.GetRangeInches();
        ultraRight.Ping();
        int rightDist = ultraRight.GetRangeInches();
        return ((leftDist + rightDist) / 2);
}
