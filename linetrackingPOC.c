#pragma config(Sensor, in2,    lineTracker,         sensorLineFollower)
#pragma config(Motor,  port1,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port10,           leftMotor,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*    NOTES:                                                                                          *|
|*    Lighting conditions, line darkness, and surface lightness change from place to place,           *|
|*    so the value of 'threshold' may need to be changed to better suit your environment.             *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 2     lineTracker         VEX Light Sensor      Front-center, facing down         *|
\*-----------------------------------------------------------------------------------------------4246-*/


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(1000);          // wait 1 seconds before starting.

	int threshold = 2400;// found by taking a reading on both DARK and LIGHT surfaces, adding them together, then dividing by 2.
	int sweepStep = 0;
	int sweepCount =0;
	// move forward for 500 msec then check steering
	//motor[leftMotor]  = 63;
	//motor[rightMotor] = 63;
	//wait1Msec(500);
	// start line following
	while(true)
	{
		// sensor sees light:
		if(SensorValue(lineTracker) > threshold){
			// proceed forward:
			motor[leftMotor]  = 63;
			motor[rightMotor] = 63;
			} else {
			sweepStep = 0;
			sweepCount = 0;
			sweepStep = 50;
			int lastDiff = threshold - SensorValue(lineTracker);
			motor[leftMotor]  = 0;
			motor[rightMotor] = 63;
			wait1Msec(sweepStep);
			int currentDiff = threshold - SensorValue(lineTracker);
			bool leftTurnLast = true;
			bool rightTurnLast = false;
			while (SensorValue(lineTracker) < threshold){
				if (currentDiff > lastDiff){
					// Further away turn back
					if (leftTurnLast) {
						lastDiff = currentDiff;
						motor[leftMotor]  = 63;
						motor[rightMotor] = 0;
						wait1Msec(sweepStep*2);
						leftTurnLast = false;
						rightTurnLast = true;
						currentDiff = threshold - SensorValue(lineTracker);
						} else {
						lastDiff = currentDiff;
						motor[leftMotor] = 0;
						motor[rightMotor] = 63;
						wait1Msec(sweepStep*2);
						leftTurnLast = true;
						rightTurnLast = false;
						currentDiff = threshold - SensorValue(lineTracker);
					}
				}
				if (currentDiff < lastDiff){
					// Closer keep going
					if (leftTurnLast) {
						lastDiff = currentDiff;
						motor[leftMotor]  = 0;
						motor[rightMotor] = 63;
						wait1Msec(sweepStep);
						leftTurnLast = true;
						rightTurnLast = false;
						currentDiff = threshold - SensorValue(lineTracker);
						} else {
						lastDiff = currentDiff;
						motor[leftMotor] = 63;
						motor[rightMotor] = 0;
						wait1Msec(sweepStep);
						leftTurnLast = false;
						rightTurnLast = true;
						currentDiff = threshold - SensorValue(lineTracker);
					}
				}
				if (currentDiff == lastDiff){
					// That's weird ... keeping going?
					if (leftTurnLast) {
						lastDiff = currentDiff;
						motor[leftMotor]  = 0;
						motor[rightMotor] = 63;
						wait1Msec(sweepStep);
						leftTurnLast = false;
						rightTurnLast = true;
						currentDiff = threshold - SensorValue(lineTracker);
						} else {
						lastDiff = currentDiff;
						motor[leftMotor] = 63;
						motor[rightMotor] = 0;
						wait1Msec(sweepStep);
						leftTurnLast = true;
						rightTurnLast = false;
						currentDiff = threshold - SensorValue(lineTracker);
					}
				}
			}
		}
	}
	//wait1Msec(25);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
