#include "quadruped.h"

Quadruped::Quadruped(RobotLeg *rearLeft, RobotLeg *rearRight, RobotLeg *frontRight, RobotLeg *frontLeft) {
  this->rearLeft = rearLeft;
  this->rearRight = rearRight;
  this->frontRight = frontRight;
  this->frontLeft = frontLeft;
}

void Quadruped::initialise() {
  this->rearLeft->moveLegAbs(-100, -100, 0, -1);
  this->rearRight->moveLegAbs(100, -100, 0, -1);
  this->frontRight->moveLegAbs(100, 100, 0, -1);
  this->frontLeft->moveLegAbs(-100, 100, 0, -1);
}

void Quadruped::waiting() {
  this->rearLeft->moveLegAbs(-80, -80, 0, 750);
  this->rearRight->moveLegAbs(80, -80, 0, 750);
  this->frontRight->moveLegAbs(80, 80, 0, 750);
  this->frontLeft->moveLegAbs(-80, 80, 0, 750);
}

void Quadruped::walkInit() {
  this->rearLeft->moveLegAbs(-WALK_X, -(WALK_STEP_B / 2) - WALK_STEP_F, WALK_FLOOR, 750);
  this->rearRight->moveLegAbs(WALK_X, -WALK_STEP_B, WALK_FLOOR, 750);
  this->frontRight->moveLegAbs(WALK_X, WALK_STEP_F, WALK_FLOOR, 750);
  this->frontLeft->moveLegAbs(-WALK_X, (WALK_STEP_B / 2) - WALK_STEP_F, WALK_FLOOR, 750);
}

void Quadruped::walk() {
  // TODO: this relative move for each leg in turn RR,FR, BODY, RL, FL, BODY

  // LEG
//  {0, 0, WALK_HEIGHT}, // raise
//  {0, WALK_STEP_B, 0}, // move
//  {0, 0, -WALK_HEIGHT}, // lower

  // BODY
//  {0, -WALK_STEP_B / 2, 0}, // forward


}
