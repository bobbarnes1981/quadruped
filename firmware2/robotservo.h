#ifndef H_ROBOTSERVO
#define H_ROBOTSERVO

#include <Arduino.h>

class RobotServo {
  private:
    int servoNumber;
    int offset;
    int dir;
    int minPulse;
    int maxPulse;
    int minAngle;
    int maxAngle;
    void pulse(int pulseLength, int uss);
    double mapDouble(double x, double in_min, double in_max, double out_min, double out_max);
  public:
    RobotServo(int servoNumber, int offset, int dir, int minPulse, int maxPulse, int minAngle, int maxAngle);
    void angle(double angleDegrees, int uss);
};

#endif
