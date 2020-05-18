#ifndef ROBOTLEG_H
#define ROBOTLEG_H

#include <Arduino.h>
#include "RobotServo.h"

class RobotLeg {
  private:
    double lengthFemur;
    double lengthTibia;
    double currentX;
    double currentY;
    double currentZ;
    double offsetX;
    double offsetY;
    double offsetZ;
    double dirX;
    double dirY;
    RobotServo *hip;
    RobotServo *thigh;
    RobotServo *knee;
    void setPosition(double x, double y, double z);
    void solve3DOF(double tx, double ty, double tz);
    void solve2DOF(double tx, double ty);
    double radToDeg(double rad);
  public:
    RobotLeg(double lengthFemur, double lengthTibia, double dirX, double dirY, RobotServo *hip, RobotServo *thigh, RobotServo *knee);
    void moveLegAbs(double x, double y, double z);
    void moveLegRel(double x, double y, double z);
    void setOffset(double x, double y, double z);
};

#endif
