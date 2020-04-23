#include "RobotServo.h"

// TODO: allow commands to move servo to specified PWM or angle, servo specific mapping of angle/pwm and limits

RobotServo::RobotServo(Adafruit_PWMServoDriver *pwm, int servoNumber, double minPulse, double maxPulse, double minLimit, double maxLimit) {
  this->pwm = pwm;
  this->servoNumber = servoNumber;
  // TODO: minPulse should not be greater than minLimit, maxPulse should not be less than maxLimit
  this->minPulse = minPulse;
  this->maxPulse = maxPulse;
  this->minLimit = minLimit;
  this->maxLimit = maxLimit;
}

RobotServo::~RobotServo() {
  
}

void RobotServo::pulse(double pulseLength) {
  if (pulseLength < minPulse) {
    pulseLength = minPulse;
  }
  if (pulseLength < minLimit) {
    pulseLength = minLimit;
  }
  if (pulseLength > maxPulse) {
    pulseLength = maxPulse;
  }
  if (pulseLength > maxLimit) {
    pulseLength = maxLimit;
  }
  this->pwm->setPWM(this->servoNumber, 0, pulseLength / (0.020 / 4096));
}

void RobotServo::angle(double angleDegrees) {
  Serial.println(this->doubleMap(angleDegrees, -90, 90, this->minPulse, this->maxPulse), 2);
  this->pulse(this->doubleMap(angleDegrees, -90, 90, this->minPulse, this->maxPulse));
}

double RobotServo::doubleMap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
