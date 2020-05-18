#include "RobotServo.h"

RobotServo::RobotServo(int servoNumber, double offset, double dir, double minPulse, double maxPulse, double minAngle, double maxAngle) {
  this->servoNumber = servoNumber;
  this->offset = offset;
  this->dir = dir;
  this->minPulse = minPulse;
  this->maxPulse = maxPulse;
  this->minAngle = minAngle;
  this->maxAngle = maxAngle;
}

// set servo to specified angle (adjusts for offset and direction of servo)
void RobotServo::angle(double angleDegrees) {
  double adjustedAngle = this->offset + (angleDegrees * this->dir);
  this->pulse(this->doubleMap(adjustedAngle, this->minAngle, this->maxAngle, this->minPulse, this->maxPulse));
}

// set the servo to the specified pulse width (restricts the servo to the specified bounds)
void RobotServo::pulse(double pulseLength) {
  if (pulseLength < this->minPulse) {
    pulseLength = this->minPulse;
  }
  if (pulseLength > this->maxPulse) {
    pulseLength = this->maxPulse;
  }

  Serial.print('#');
  Serial.print(this->servoNumber);
  Serial.print('P');
  Serial.print((int)(pulseLength * 1000000));
  Serial.print('T');
  Serial.print(1000);
  Serial.print('\r');
}

// implementation of arduino map function for double type
double RobotServo::doubleMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
