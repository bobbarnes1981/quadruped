#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#ifdef CALIBRATION
#include "Calibration.h"
#endif

#define SERVO_FREQ 50       // Analog servos run at ~50 Hz updates

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define OSC_FREQ 26660574   // measured using arduino nano with pulseIn

// TODO: maybe replace classes with functions instead, to save on memory

#ifdef CALIBRATION
Calibration calibration = Calibration(&pwm);
#endif

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

#define LENGTH_FEMUR 59.0
#define LENGTH_TIBIA 122.0

#include "RobotServo.h"
#include "RobotLeg.h"
#include "Quadruped.h"

RobotServo servoRL_HIP = RobotServo(&pwm, RL_HIP, -45, 1, 0.001000, 0.001950, -45, 45);
RobotServo servoRL_THIGH = RobotServo(&pwm, RL_THIGH, 0, 1, 0.001100, 0.002450, -38, 90);
RobotServo servoRL_KNEE = RobotServo(&pwm, RL_KNEE, 90, -1, 0.000700, 0.002050, -90, 38);
RobotLeg legRL = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, -1, -1,
                   &servoRL_HIP,
                   &servoRL_THIGH,
                   &servoRL_KNEE
                 );

RobotServo servoRR_HIP = RobotServo(&pwm, RR_HIP, 45, -1, 0.001100, 0.002050, -45, 45);
RobotServo servoRR_THIGH = RobotServo(&pwm, RR_THIGH, 0, -1, 0.000600, 0.001950, -90, 38);
RobotServo servoRR_KNEE = RobotServo(&pwm, RR_KNEE, -90, 1, 0.001000, 0.002350, -38, 90);
RobotLeg legRR = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, 1, -1,
                   &servoRR_HIP,
                   &servoRR_THIGH,
                   &servoRR_KNEE
                 );

RobotServo servoFR_HIP = RobotServo(&pwm, FR_HIP, -45, 1, 0.001050, 0.001950, -45, 45);
RobotServo servoFR_THIGH = RobotServo(&pwm, FR_THIGH, 0, 1, 0.001050, 0.002400, -38, 90);
RobotServo servoFR_KNEE = RobotServo(&pwm, FR_KNEE, 90, -1, 0.000800, 0.002150, -90, 38);
RobotLeg legFR = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, 1, 1,
                   &servoFR_HIP,
                   &servoFR_THIGH,
                   &servoFR_KNEE
                 );

RobotServo servoFL_HIP = RobotServo(&pwm, FL_HIP, 45, -1, 0.001100, 0.002000, -45, 45);
RobotServo servoFL_THIGH = RobotServo(&pwm, FL_THIGH, 0, -1, 0.000650, 0.001950, -90, 38);
RobotServo servoFL_KNEE = RobotServo(&pwm, FL_KNEE, -90, 1, 0.001000, 0.002350, -38, 90);
RobotLeg legFL = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, -1, 1,
                   &servoFL_HIP,
                   &servoFL_THIGH,
                   &servoFL_KNEE
                 );

Quadruped quadruped = Quadruped(&legRL, &legRR, &legFR, &legFL);

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
State currentState = state_startup;

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  pwm.begin();
  pwm.setOscillatorFrequency(OSC_FREQ);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  legRL.moveLeg(-100, -100, 0);
  legRR.moveLeg(100, -100, 0);
  legFR.moveLeg(100, 100, 0);
  legFL.moveLeg(-100, 100, 0);
  legRL.setAbsoluteTarget(-100, -100, 0);
  legRR.setAbsoluteTarget(100, -100, 0);
  legFR.setAbsoluteTarget(100, 100, 0);
  legFL.setAbsoluteTarget(-100, 100, 0);

  delay(1000);

  lastMillis = millis();
}

int currentStep = -1;
double position_startup[][4][3] = {{
    { -80, -80, 0},
    {80, -80, 0},
    {80, 80, 0},
    { -80, 80, 0}
}};

#define WALK_X 80
#define WALK_STEP_F 10
#define WALK_STEP_B 100
#define WALK_FLOOR -70
#define WALK_HEIGHT 40
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

double offsetx = 0;
double offsety = 0;
double offsetz = 0;
void loop() {
#ifdef CALIBRATION
  calibration.processCommand();
#else

  unsigned long currentMillis = millis();
  unsigned long elapsedMillis = currentMillis - lastMillis;
  lastMillis = currentMillis;
  //Serial.println(elapsedMillis);

  if (Serial.available()) {
    int s = Serial.read();
    Serial.println(s);
    if (s == 's') {
      currentStep = -1;
      currentState = state_startup;
    }
    if (s == 'k') {
      currentStep = -1;
      currentState = state_kinematics;
    }
    if (s == 'w') {
      currentStep = -1;
      currentState = state_stand;
    }
    if (s == 'u') {
      offsetz -= 10;
    }
    if (s == 'd') {
      offsetz += 10;
    }
    if (s == 'l') {
      offsetx += 10;
    }
    if (s == 'r') {
      offsetx -= 10;
    }
    if (s == 'f') {
      offsety -= 10;
    }
    if (s == 'b') {
      offsety += 10;
    }
    // todo: move this to testing state
    legRL.setOffset(-offsetx, -offsety, offsetz);
    legRR.setOffset(offsetx, -offsety, offsetz);
    legFR.setOffset(offsetx, offsety, offsetz);
    legFL.setOffset(-offsetx, offsety, offsetz);
  }

  switch (currentState) {
    case state_startup:
      moveAbsolutes(elapsedMillis, position_startup, sizeof(position_startup) / sizeof(position_startup[0]), state_waiting);
      break;
    case state_kinematics:
      legRL.updateLeg(elapsedMillis);
      legRR.updateLeg(elapsedMillis);
      legFR.updateLeg(elapsedMillis);
      legFL.updateLeg(elapsedMillis);
      break;
    case state_stand:
      moveAbsolutes(elapsedMillis, position_stand, sizeof(position_stand) / sizeof(position_stand[0]), state_walk_rear_right);
      break;
    case state_walk_rear_right:
      moveRelative(elapsedMillis, &legRR, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_front_right);
      break;
    case state_walk_front_right:
      moveRelative(elapsedMillis, &legFR, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_body_right);
      break;
    case state_walk_body_right:
      moveRelatives(elapsedMillis, move_body, sizeof(move_body) / sizeof(move_body[0]), state_walk_rear_left);
      break;
    case state_walk_rear_left:
      moveRelative(elapsedMillis, &legRL, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_front_left);
      break;
    case state_walk_front_left:
      moveRelative(elapsedMillis, &legFL, move_leg, sizeof(move_leg) / sizeof(move_leg[0]), state_walk_body_left);
      break;
    case state_walk_body_left:
      moveRelatives(elapsedMillis, move_body, sizeof(move_body) / sizeof(move_body[0]), state_waiting);
      break;
    case state_waiting:
      // nothing yet
      break;
  }

#endif
}

void moveAbsolutes(double elapsedMillis, double cycle[][4][3], int steps, State nextState) {
  if (!legRL.isMoving() && !legRR.isMoving() && !legFR.isMoving() && !legFL.isMoving()) {
    // get next
    currentStep++;
    if (currentStep >= steps) {
      // no more steps, stop
      currentStep = -1;
      currentState = nextState;
    } else {
      // set next target
      legRL.setAbsoluteTarget(cycle[currentStep][RL_LEG][0], cycle[currentStep][RL_LEG][1], cycle[currentStep][RL_LEG][2]);
      legRR.setAbsoluteTarget(cycle[currentStep][RR_LEG][0], cycle[currentStep][RR_LEG][1], cycle[currentStep][RR_LEG][2]);
      legFR.setAbsoluteTarget(cycle[currentStep][FR_LEG][0], cycle[currentStep][FR_LEG][1], cycle[currentStep][FR_LEG][2]);
      legFL.setAbsoluteTarget(cycle[currentStep][FL_LEG][0], cycle[currentStep][FL_LEG][1], cycle[currentStep][FL_LEG][2]);
    }
  } else {
    // still need to move
    legRL.updateLeg(elapsedMillis);
    legRR.updateLeg(elapsedMillis);
    legFR.updateLeg(elapsedMillis);
    legFL.updateLeg(elapsedMillis);
  }
}

void moveRelatives(double elapsedMillis, double cycle[][3], int steps, State nextState) {
  if (!legRL.isMoving() && !legRR.isMoving() && !legFR.isMoving() && !legFL.isMoving()) {
    // get next
    currentStep++;
    if (currentStep >= steps) {
      // no more steps, stop
      currentStep = -1;
      currentState = nextState;
    } else {
      // set next target
      legRR.setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
      legRL.setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
      legFL.setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
      legFR.setRelativeTarget(cycle[currentStep][0], cycle[currentStep][1], cycle[currentStep][2]);
    }
  } else {
    // still need to move
    legRR.updateLeg(elapsedMillis);
    legRL.updateLeg(elapsedMillis);
    legFL.updateLeg(elapsedMillis);
    legFR.updateLeg(elapsedMillis);
  }
}

void moveRelative(double elapsedMillis, RobotLeg *leg, double cycle[][3], int steps, State nextState) {
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
