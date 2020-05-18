#include "Quadruped.h"

// TODO: allow commands for walk, etc...

double position_startup[][4][3] = {{
    { -80, -80, 0},
    {80, -80, 0},
    {80, 80, 0},
    { -80, 80, 0}
}};
double position_stand[][4][3] = {{
    {-WALK_X, -(WALK_STEP_B / 2) - WALK_STEP_F, WALK_FLOOR},
    {WALK_X, -WALK_STEP_B, WALK_FLOOR},
    {WALK_X, WALK_STEP_F, WALK_FLOOR},
    {-WALK_X, (WALK_STEP_B / 2) - WALK_STEP_F, WALK_FLOOR}
  }
};
double move_leg[][3] = {
  {0, 0, WALK_HEIGHT}, // raise
  {0, WALK_STEP_B, 0}, // move
  {0, 0, -WALK_HEIGHT}, // lower
};
double move_body[][3] = {
  {0, -WALK_STEP_B / 2, 0}, // forward
};

Quadruped::Quadruped(RobotLeg *legRL, RobotLeg *legRR, RobotLeg *legFR, RobotLeg *legFL) {
  this->legRL = legRL;
  this->legRR = legRR;
  this->legFR = legFR;
  this->legFL = legFL;
  this->startup();
}

Quadruped::~Quadruped() {
  
}

void Quadruped::initialise() {
  legRL->moveLeg(-100, -100, 0);
  legRR->moveLeg(100, -100, 0);
  legFR->moveLeg(100, 100, 0);
  legFL->moveLeg(-100, 100, 0);
  legRL->setAbsoluteTarget(-100, -100, 0);
  legRR->setAbsoluteTarget(100, -100, 0);
  legFR->setAbsoluteTarget(100, 100, 0);
  legFL->setAbsoluteTarget(-100, 100, 0);

  delay(1000);
}

void Quadruped::updateQuadruped(double elapsedMillis) {
  switch (currentState) {
    case state_startup:
      moveAbsolutes(elapsedMillis, position_startup, sizeof(position_startup) / sizeof(position_startup[0]), state_waiting);
      break;
    case state_kinematics:
      legRL->updateLeg(elapsedMillis);
      legRR->updateLeg(elapsedMillis);
      legFR->updateLeg(elapsedMillis);
      legFL->updateLeg(elapsedMillis);
      break;
    case state_stand:
      moveAbsolutes(elapsedMillis, position_stand, sizeof(position_stand) / sizeof(position_stand[0]), state_walk_rear_right);
      break;
    case state_walk_rear_right:
      moveRelative(elapsedMillis, this->legRR, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_front_right);
      break;
    case state_walk_front_right:
      moveRelative(elapsedMillis, this->legFR, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_body_right);
      break;
    case state_walk_body_right:
      moveRelatives(elapsedMillis, move_body, sizeof(move_body) / sizeof(move_body[0]), state_walk_rear_left);
      break;
    case state_walk_rear_left:
      moveRelative(elapsedMillis, this->legRL, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_front_left);
      break;
    case state_walk_front_left:
      this->moveRelative(elapsedMillis, this->legFL, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_body_left);
      break;
    case state_walk_body_left:
      moveRelatives(elapsedMillis, move_body, sizeof(move_body) / sizeof(move_body[0]), state_waiting);
      break;
    case state_waiting:
      // nothing yet
      break;
  }
}

void Quadruped::moveAbsolutes(double elapsedMillis, double cycle[][4][3], int steps, State nextState) {
  if (!legRL->isMoving() && !legRR->isMoving() && !legFR->isMoving() && !legFL->isMoving()) {
    // get next
    currentStep++;
    if (currentStep >= steps) {
      // no more steps, stop
      currentStep = -1;
      currentState = nextState;
    } else {
      // set next target
      legRL->setAbsoluteTarget(cycle[currentStep][RL_LEG][0], cycle[currentStep][RL_LEG][1], cycle[currentStep][RL_LEG][2]);
      legRR->setAbsoluteTarget(cycle[currentStep][RR_LEG][0], cycle[currentStep][RR_LEG][1], cycle[currentStep][RR_LEG][2]);
      legFR->setAbsoluteTarget(cycle[currentStep][FR_LEG][0], cycle[currentStep][FR_LEG][1], cycle[currentStep][FR_LEG][2]);
      legFL->setAbsoluteTarget(cycle[currentStep][FL_LEG][0], cycle[currentStep][FL_LEG][1], cycle[currentStep][FL_LEG][2]);
    }
  } else {
    // still need to move
    legRL->updateLeg(elapsedMillis);
    legRR->updateLeg(elapsedMillis);
    legFR->updateLeg(elapsedMillis);
    legFL->updateLeg(elapsedMillis);
  }
}

void Quadruped::moveRelatives(double elapsedMillis, double cycle[][3], int steps, State nextState) {
  if (!legRL->isMoving() && !legRR->isMoving() && !legFR->isMoving() && !legFL->isMoving()) {
    // get next
    currentStep++;
    if (currentStep >= steps) {
      // no more steps, stop
      currentStep = -1;
      currentState = nextState;
    } else {
      // set next target
      legRR->setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
      legRL->setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
      legFL->setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
      legFR->setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
    }
  } else {
    // still need to move
    legRR->updateLeg(elapsedMillis);
    legRL->updateLeg(elapsedMillis);
    legFL->updateLeg(elapsedMillis);
    legFR->updateLeg(elapsedMillis);
  }
}

void Quadruped::moveRelative(double elapsedMillis, RobotLeg *leg, double cycle[][3], int steps, State nextState) {
  if (!leg->isMoving()) {
    // get next
    currentStep++;
    if (currentStep >= steps) {
      // no more steps, stop
      currentStep = -1;
      currentState = nextState;
    } else {
      // set next target
      leg->setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
    }
  } else {
    // still need to move
    leg->updateLeg(elapsedMillis);
  }
}

void Quadruped::walk() {
  currentStep = -1;
  currentState = state_stand;
}

void Quadruped::kinematics() {
  currentStep = -1;
  currentState = state_kinematics;
}

void Quadruped::startup() {
  currentStep = -1;
  currentState = state_startup;
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
