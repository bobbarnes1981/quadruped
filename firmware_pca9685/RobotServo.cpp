#include "RobotServo.h"

RobotServo::RobotServo(Adafruit_PWMServoDriver *pwm, int servoNumber, double offset, double dir, double minPulse, double maxPulse, double minAngle, double maxAngle) {
  this->pwm = pwm;
  this->servoNumber = servoNumber;
  this->offset = offset;
  this->dir = dir;
  this->minPulse = minPulse;
  this->maxPulse = maxPulse;
  this->minAngle = minAngle;
  this->maxAngle = maxAngle;
}

RobotServo::~RobotServo() {
  
}

// set the servo to the specified pulse width (restricts the servo to the specified bounds)
void RobotServo::pulse(double pulseLength) {
  if (pulseLength < this->minPulse) {
    pulseLength = this->minPulse;
    Serial.print("min limit");
    Serial.println(pulseLength, 6);
  }
  if (pulseLength > this->maxPulse) {
    pulseLength = this->maxPulse;
    Serial.print("max limit");
    Serial.println(pulseLength, 6);
  }
  this->pwm->setPWM(this->servoNumber, 0, pulseLength / (0.020 / 4096));
}

// set servo to specified angle (adjusts for offset and direction of servo)
void RobotServo::angle(double angleDegrees) {
  double adjustedAngle = this->offset + (angleDegrees * this->dir);
  this->pulse(this->doubleMap(adjustedAngle, this->minAngle, this->maxAngle, this->minPulse, this->maxPulse));
}

// implementation of arduino map function for double type
double RobotServo::doubleMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
