#ifndef ROBOTSERVO_H
#define ROBOTSERVO_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

class RobotServo {
  private:
    Adafruit_PWMServoDriver *pwm;
    int servoNumber;
    double minPulse;
    double maxPulse;
    double minLimit;
    double maxLimit;
  public:
    RobotServo(Adafruit_PWMServoDriver *pwm, int servoNumber, double minPulse, double maxPulse, double minLimit, double maxLimit);
    ~RobotServo();
    void pulse(double pulseLength);
    void angle(double angleDegrees);
    double doubleMap(double x, double in_min, double in_max, double out_min, double out_max);
};

#endif
