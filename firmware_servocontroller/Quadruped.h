#ifndef QUADRUPED_H
#define QUADRUPED_H

#include <Arduino.h>
#include "RobotLeg.h"

#define RL_LEG 0
#define RL_HIP 9
#define RL_THIGH 10
#define RL_KNEE 11

#define RR_LEG 1
#define RR_HIP 6
#define RR_THIGH 7
#define RR_KNEE 8

#define FR_LEG 2
#define FR_HIP 3
#define FR_THIGH 4
#define FR_KNEE 5

#define FL_LEG 3
#define FL_HIP 0
#define FL_THIGH 1
#define FL_KNEE 2

#define WALK_X 100 // Increased from 80 so legs don't move too close to body
#define WALK_STEP_F 10
#define WALK_STEP_B 100
#define WALK_FLOOR -70
#define WALK_HEIGHT 40

class Quadruped {
  private:
    RobotLeg *legRL;
    RobotLeg *legRR;
    RobotLeg *legFR;
    RobotLeg *legFL;
    double offsetX;
    double offsetY;
    double offsetZ;
    void walkLeg(RobotLeg *leg);
    void walkBody();
  public:
    Quadruped(RobotLeg *legRL, RobotLeg *legRR, RobotLeg *legFR, RobotLeg *legFL);
    void initialise();
    void stateStartup();
    void stateWalkReady();
    void stateWalking();
    void stateDemo();
    
    void alterOffsets(double x, double y, double z);
};

#endif
