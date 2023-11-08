#pragma config(Sensor, in1,    lineFollower,  sensorLineFollower)
#pragma config(Motor,  port2,  leftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,  rightMotor,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const float Kp = 0.5;
const float Ki = 0.01;
const float Kd = 0;

int error = 0;
int integral = 0;  
int lastError = 0;
int derivative = 0;

task main() {
  wait1Msec(500); // Wait for 500 milliseconds to initialize

  while(true) {
    int targetValue = 2000; // You will need to calibrate this value based on your sensor's behavior
    error = SensorValue[lineFollower] - targetValue;

    // Prevent integral windup
    if (abs(error) < targetValue) {
      integral += error;
    } else {
      integral = 0; // Reset integral if error is too large
    }

    derivative = error - lastError;
    lastError = error;

    // Calculate motor power, ensuring it does not exceed the motor's limits
    int motorPowerLeft = Kp * error + Ki * integral + Kd * derivative;
    int motorPowerRight = Kp * error - Ki * integral - Kd * derivative;

    // Clamp the motor power to the max and min motor power range
    motorPowerLeft = motorPowerLeft > 127 ? 127 : motorPowerLeft < -127 ? -127 : motorPowerLeft;
    motorPowerRight = motorPowerRight > 127 ? 127 : motorPowerRight < -127 ? -127 : motorPowerRight;

    motor[leftMotor] = motorPowerLeft; 
    motor[rightMotor] = motorPowerRight;

    wait1Msec(25); // Wait for 25 milliseconds to control the loop rate
  }
}
