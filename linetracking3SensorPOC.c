#pragma config(Sensor, in1,    lineTrackerRight, sensorLineFollower)
#pragma config(Sensor, in2,    lineTrackerCenter, sensorLineFollower)
#pragma config(Sensor, in3,    lineTrackerLeft, sensorLineFollower)
#pragma config(Motor,  port1,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          leftMotor,     tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  // Wait 1 second before starting
  wait1Msec(1000);

  // This threshold will have to be adjusted depending on the environment and
  // the line being tracked.  You may also have to invert the comparisons if
  // you are tracking a "dark" line instead of "light" line.
  int threshold = 2400;

  // loopDelay controls how often the robot will check the sensor and align.
  int loopDelay = 25;

  // start line following
  while(true)
  {
    // Right sensor trigger:
    if(SensorValue(lineTrackerRight) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = 63;
      motor[rightMotor] = 0;
    }
    // Center sensor trigger:
    if(SensorValue(lineTrackerCenter) > threshold)
    {
      // go straight
      motor[leftMotor]  = 63;
      motor[rightMotor] = 63;
    }
    // Left sensor trigger:
    if(SensorValue(lineTrackerLeft) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = 63;
    }
  }
  wait1Msec(loopDelay);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
