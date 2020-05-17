#ifndef ROBOTSERVO_H
#define ROBOTSERVO_H

#include <Arduino.h>

class RobotServo {
  private:
    int servoNumber;
    double offset;
    double dir;
    double minPulse;
    double maxPulse;
    double minAngle;
    double maxAngle;
  public:
    RobotServo(int servoNumber, double offset, double dir, double minPulse, double maxPulse, double minAngle, double maxAngle);
    void pulse(double pulseLength);
    void angle(double angleDegrees);
    double doubleMap(double x, double in_min, double in_max, double out_min, double out_max);
};

#endif
