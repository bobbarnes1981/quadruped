#ifndef QUADRUPED_H
#define QUADRUPED_H

#include <Arduino.h>
#include "RobotLeg.h"

class Quadruped {
  private:
    RobotLeg *legRL;
    RobotLeg *legRR;
    RobotLeg *legFR;
    RobotLeg *legFL;
  public:
    Quadruped(RobotLeg *legRL, RobotLeg *legRR, RobotLeg *legFR, RobotLeg *legFL);
    ~Quadruped();
};

#endif
