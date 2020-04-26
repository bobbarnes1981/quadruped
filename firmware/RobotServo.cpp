#include "RobotServo.h"

#define PULSE_SCALE 0.020 / 4096 // 4096 steps in 50Hz

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
    // TODO: warning
  }
  if (pulseLength > this->maxPulse) {
    pulseLength = this->maxPulse;
    // TODO: warning
  }
  this->pwm->setPWM(this->servoNumber, 0, pulseLength / PULSE_SCALE);
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
