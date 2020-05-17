#ifndef H_ROBOTLEG
#define H_ROBOTLEG

#include "robotservo.h"

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
    void solve3DOF(double tx, double ty, double tz, int uss);
    void solve2DOF(double tx, double ty, int uss);
    double radToDeg(double rad);
  public:
    RobotLeg(double lengthFemur, double lengthTibia, double dirX, double dirY, RobotServo *hip, RobotServo *thigh, RobotServo *knee);
    void moveLegAbs(int x, int y, int z, int uss);
    void moveLegRel(int x, int y, int z, int uss);
};

#endif
