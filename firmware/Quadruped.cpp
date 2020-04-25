#include "Quadruped.h"

// TODO: allow commands for walk, etc...

Quadruped::Quadruped(RobotLeg *legRL, RobotLeg *legRR, RobotLeg *legFR, RobotLeg *legFL) {
  this->legRL = legRL;
  this->legRR = legRR;
  this->legFR = legFR;
  this->legFL = legFL;
}

Quadruped::~Quadruped() {
  
}
