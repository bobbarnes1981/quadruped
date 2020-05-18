#ifndef QUADRUPED_H
#define QUADRUPED_H

#include <Arduino.h>
#include "RobotLeg.h"

#define RL_LEG 0
#define RL_HIP 0
#define RL_THIGH 1
#define RL_KNEE 2

#define RR_LEG 1
#define RR_HIP 4
#define RR_THIGH 5
#define RR_KNEE 6

#define FR_LEG 2
#define FR_HIP 8
#define FR_THIGH 9
#define FR_KNEE 10

#define FL_LEG 3
#define FL_HIP 12
#define FL_THIGH 13
#define FL_KNEE 14

#define WALK_X 80
#define WALK_STEP_F 10
#define WALK_STEP_B 100
#define WALK_FLOOR -70
#define WALK_HEIGHT 40

enum State {
  state_startup,
  state_kinematics,
  state_waiting,

  state_stand,
  state_walk_rear_right,
  state_walk_front_right,
  state_walk_body_right,
  state_walk_rear_left,
  state_walk_front_left,
  state_walk_body_left,
};

class Quadruped {
  private:
    RobotLeg *legRL;
    RobotLeg *legRR;
    RobotLeg *legFR;
    RobotLeg *legFL;
    double offsetX;
    double offsetY;
    double offsetZ;
    State currentState;
    int currentStep;
    void moveAbsolutes(double elapsedMillis, double cycle[][4][3], int steps, State nextState);
    void moveRelatives(double elapsedMillis, double cycle[][3], int steps, State nextState);
    void moveRelative(double elapsedMillis, RobotLeg *leg, double cycle[][3], int steps, State nextState);
  public:
    Quadruped(RobotLeg *legRL, RobotLeg *legRR, RobotLeg *legFR, RobotLeg *legFL);
    ~Quadruped();
    void initialise();
    void updateQuadruped(double elapsedMillis);
    void startup();
    void kinematics();
    void walk();
    void alterOffsets(double x, double y, double z);
};

#endif
