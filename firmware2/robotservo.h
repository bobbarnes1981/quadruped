#ifndef H_ROBOTSERVO
#define H_ROBOTSERVO

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
    void pulse(int pulseLength, int uss);
    double mapDouble(double x, double in_min, double in_max, double out_min, double out_max);
  public:
    RobotServo(int servoNumber, double offset, double dir, double minPulse, double maxPulse, double minAngle, double maxAngle);
    void angle(double angleDegrees, int uss);
};

#endif
