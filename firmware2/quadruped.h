#ifndef H_QUADRUPED
#define H_QUADRUPED

#include "robotleg.h"
#include "config.h"

class Quadruped {
  private:
    RobotLeg *rearLeft;
    RobotLeg *rearRight;
    RobotLeg *frontRight;
    RobotLeg *frontLeft;
  public:
    Quadruped(RobotLeg *rearLeft, RobotLeg *rearRight, RobotLeg *frontRight, RobotLeg *frontLeft);
    void initialise();
    void waiting();
    void walkInit();
};

#endif
