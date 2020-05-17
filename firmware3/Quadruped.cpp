#include "Quadruped.h"

Quadruped::Quadruped(RobotLeg *legRL, RobotLeg *legRR, RobotLeg *legFR, RobotLeg *legFL) {
  this->legRL = legRL;
  this->legRR = legRR;
  this->legFR = legFR;
  this->legFL = legFL;
}

void Quadruped::initialise() {
  legRL->moveLeg(-100, -100, 0);
  legRR->moveLeg(100, -100, 0);
  legFR->moveLeg(100, 100, 0);
  legFL->moveLeg(-100, 100, 0);

  delay(1000);
}

void Quadruped::stateStartup() {
  this->legRL->moveLeg(-80, -80, 0);
  this->legRR->moveLeg(80, -80, 0);
  this->legFR->moveLeg(80, 80, 0);
  this->legFL->moveLeg(-80, 80, 0);
}

void Quadruped::stateWalkReady() {
  this->legRL->moveLeg(-WALK_X, -(WALK_STEP_B / 2) - WALK_STEP_F, WALK_FLOOR);
  this->legRR->moveLeg(WALK_X, -WALK_STEP_B, WALK_FLOOR);
  this->legFR->moveLeg(WALK_X, WALK_STEP_F, WALK_FLOOR);
  this->legFL->moveLeg(-WALK_X, (WALK_STEP_B / 2) - WALK_STEP_F, WALK_FLOOR);
}

void Quadruped::stateWalking() {
  // FIXME: horrible hack...
  this->walkLeg(this->legRR);
  this->walkLeg(this->legFR);
  this->walkBody();
  this->walkLeg(this->legRL);
  this->walkLeg(this->legFL);
  this->walkBody();
}

void Quadruped::walkLeg(RobotLeg *leg) {
  leg->moveLegRel(0, 0, WALK_HEIGHT); // raise
  delay(1000);
  leg->moveLegRel(0, WALK_STEP_B, 0); // move
  delay(1000);
  leg->moveLegRel(0, 0, -WALK_HEIGHT); // lower
  delay(1000);
}

void Quadruped::walkBody() {
  this->legRL->moveLegRel(0, -WALK_STEP_B / 2, 0);
  this->legRR->moveLegRel(0, -WALK_STEP_B / 2, 0);
  this->legFL->moveLegRel(0, -WALK_STEP_B / 2, 0);
  this->legFR->moveLegRel(0, -WALK_STEP_B / 2, 0);
  delay(1000);
}

void Quadruped::alterOffsets(double x, double y, double z) {
  offsetX += x;
  offsetY += y;
  offsetZ += z;
  legRL->setOffset(-offsetX, -offsetY, offsetZ);
  legRR->setOffset(offsetX, -offsetY, offsetZ);
  legFR->setOffset(offsetX, offsetY, offsetZ);
  legFL->setOffset(-offsetX, offsetY, offsetZ);
}
