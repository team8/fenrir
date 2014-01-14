//Use encoders to 

//PIDController class uses PIDSource to write PIDOutput

Joystick turretStick(1); 
 Victor turretMotor(1); 
 AnalogChannel turretPot(1); 
 PIDController turretControl(0.1, 0.001, 0.0, &turretPot, &turretMotor); 
 
 turretControl.Enable(); // start calculating PIDOutput values 
 
 while(IsOperator()) 
 { 
 turretControl.SetSetpoint((turretStick.GetX() + 1.0) * 2.5); 
 Wait(.02); // wait for new joystick values 
 } 
