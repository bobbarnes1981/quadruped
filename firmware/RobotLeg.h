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
    double targetX;
    double targetY;
    double targetZ;
    double offsetX;
    double offsetY;
    double offsetZ;
    double dirX;
    double dirY;
    RobotServo *hip;
    RobotServo *thigh;
    RobotServo *knee;
    void solve3DOF(double tx, double ty, double tz);
    void solve2DOF(double tx, double ty);
    double radToDeg(double rad);
    double updateLegCoord(double distance, double current, double target);
    void setPosition(double x, double y, double z);
  public:
    RobotLeg(double lengthFemur, double lengthTibia, double dirX, double dirY, RobotServo *hip, RobotServo *thigh, RobotServo *knee);
    ~RobotLeg();
    void moveLeg(double x, double y, double z);
    void setTarget(double x, double y, double z);
    void setRelativeTarget(double x, double y, double z);
    void setOffset(double x, double y, double z);
    void updateLeg(double elapsedMillis);
    bool isMoving();
};

#endif
