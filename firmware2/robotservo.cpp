#include "robotservo.h"

RobotServo::RobotServo(int servoNumber, double offset, double dir, double minPulse, double maxPulse, double minAngle, double maxAngle) {
  this->servoNumber = servoNumber;
  this->offset = offset;
  this->dir = dir;
  this->minPulse = minPulse;
  this->maxPulse = maxPulse;
  this->minAngle = minAngle;
  this->maxAngle = maxAngle;
}

// set the servo to the specified pulse width (restricts the servo to the specified bounds)
// TODO: implement this in the servo controller
void RobotServo::pulse(int pulseLength, int uss) {
  if (pulseLength < this->minPulse) {
//    Serial.print("error-min ");
//    Serial.print(pulseLength);
//    Serial.print(" < ");
//    Serial.println(this->minPulse);
//    Serial.println(pulseLength);
    pulseLength = this->minPulse;
  }
  if (pulseLength > this->maxPulse) {
//    Serial.println("error-max");
//    Serial.println(pulseLength);
    pulseLength = this->maxPulse;
  }
  Serial.print('#');
  Serial.print(this->servoNumber);
  Serial.print('P');
  Serial.print(pulseLength);
  if (uss != -1) {
    Serial.print('S');
    Serial.print(uss);
  }
  Serial.print('\r');
}

// set servo to specified angle (adjusts for offset and direction of servo)
void RobotServo::angle(double angleDegrees, int uss) {
//  Serial.print("angle abs ");
//  Serial.println(angleDegrees);
  int adjustedAngle = this->offset + (angleDegrees * this->dir);
//  Serial.print("angle adj ");
//  Serial.println(adjustedAngle);
  int p = this->mapDouble(adjustedAngle, this->minAngle, this->maxAngle, this->minPulse, this->maxPulse);
  this->pulse(p, uss);
}

double RobotServo::mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
