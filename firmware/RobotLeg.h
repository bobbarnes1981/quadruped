#ifndef ROBOTLEG_H
#define ROBOTLEG_H

#include <Arduino.h>
#include "RobotServo.h"

class RobotLeg {
  private:
    double lengthFemur;
    double lengthTibia;
    RobotServo *hip;
    RobotServo *thigh;
    RobotServo *knee;
    void solve3DOF(double tx, double ty, double tz);
    void solve2DOF(double tx, double ty);
    double radToDeg(double rad);
  public:
    RobotLeg(double lengthFemur, double lengthTibia, RobotServo *hip, RobotServo *thigh, RobotServo *knee);
    ~RobotLeg();
    void setPosition(double x, double y, double z);
};

#endif
