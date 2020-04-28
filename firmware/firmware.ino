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
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoRL_HIP,
  &servoRL_THIGH,
  &servoRL_KNEE
);

RobotServo servoRR_HIP = RobotServo(&pwm, RR_HIP, 45, -1, 0.001100, 0.002050, -45, 45);
RobotServo servoRR_THIGH = RobotServo(&pwm, RR_THIGH,0, -1, 0.000600, 0.001950, -90, 38);
RobotServo servoRR_KNEE = RobotServo(&pwm, RR_KNEE, -90, 1, 0.001000, 0.002350, -38, 90);
RobotLeg legRR = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoRR_HIP,
  &servoRR_THIGH,
  &servoRR_KNEE
);

RobotServo servoFR_HIP = RobotServo(&pwm, FR_HIP, -45, 1, 0.001050, 0.001950, -45, 45);
RobotServo servoFR_THIGH = RobotServo(&pwm, FR_THIGH, 0, 1, 0.001050, 0.002400, -38, 90);
RobotServo servoFR_KNEE = RobotServo(&pwm, FR_KNEE, 90, -1, 0.000800, 0.002150, -90, 38);
RobotLeg legFR = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoFR_HIP,
  &servoFR_THIGH,
  &servoFR_KNEE
);

RobotServo servoFL_HIP = RobotServo(&pwm, FL_HIP, 45, -1, 0.001100, 0.002000, -45, 45);
RobotServo servoFL_THIGH = RobotServo(&pwm, FL_THIGH, 0, -1, 0.000650, 0.001950, -90, 38);
RobotServo servoFL_KNEE = RobotServo(&pwm, FL_KNEE, -90, 1, 0.001000, 0.002350, -38, 90);
RobotLeg legFL = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoFL_HIP,
  &servoFL_THIGH,
  &servoFL_KNEE
);

Quadruped quadruped = Quadruped(&legRL, &legRR, &legFR, &legFL);

enum State {
  state_startup,
  state_next,
  state_moving,
  state_waiting
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
  
  legRL.moveLeg(100, 100, 0);
  legRR.moveLeg(100, 100, 0);
  legFR.moveLeg(100, 100, 0);
  legFL.moveLeg(100, 100, 0);

  delay(2000);

  lastMillis = millis();
}

int currentStep = -1;
//double cycle_init[][4][3] = {
//  {{120, 0, 0},{120, 0, 0},{120, 0, 0},{120, 0, 0}}
//};
double cycle_init[][4][3] = {
  // touch the ground 15cm from body
  {{100, 100, -38},{100, 100, -38},{100, 100, -38},{100, 100, -38}},
  // lift legs from the ground
  {{100, 100, 0},{100, 100, 0},{100, 100, 0},{100, 100, 0}},
  // move legs in and down
  {{80, 80, -20},{80, 80, -20},{80, 80, -20},{80, 80, -20}},
  // lift body 1cm from the ground
  {{80, 80, -80},{80, 80, -80},{80, 80, -80},{80, 80, -80}},
  // lift legs back off the ground
  {{80, 80, -20},{80, 80, -20},{80, 80, -20},{80, 80, -20}},
};

double offsetx = 0;
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
      currentState = state_next;
    }
    if (s == 'u') {
      offsetz-=10;
    }
    if (s == 'd') {
      offsetz+=10;
    }
    if (s == 'l') {
      offsetx+=10;
    }
    if (s == 'r') {
      offsetx-=10;
    }
    // todo: move this to testing state
    legRL.setOffset(-offsetx, 0, offsetz);
    legRR.setOffset(offsetx, 0, offsetz);
    legFR.setOffset(offsetx, 0, offsetz);
    legFL.setOffset(-offsetx, 0, offsetz);
    legRL.updateLeg(1);
    legRR.updateLeg(1);
    legFR.updateLeg(1);
    legFL.updateLeg(1);
  }
  
  switch(currentState) {
    case state_startup:
      currentState = state_next;
      break;
    case state_next:
      currentStep++;
      if (currentStep >= sizeof(cycle_init)/sizeof(cycle_init[0])) {
        // no more steps, stop
        currentState = state_waiting;
      } else {
        // set next target
        legRL.setTarget(cycle_init[currentStep][RL_LEG][0], cycle_init[currentStep][RL_LEG][1], cycle_init[currentStep][RL_LEG][2]);
        legRR.setTarget(cycle_init[currentStep][RR_LEG][0], cycle_init[currentStep][RR_LEG][1], cycle_init[currentStep][RR_LEG][2]);
        legFR.setTarget(cycle_init[currentStep][FR_LEG][0], cycle_init[currentStep][FR_LEG][1], cycle_init[currentStep][FR_LEG][2]);
        legFL.setTarget(cycle_init[currentStep][FL_LEG][0], cycle_init[currentStep][FL_LEG][1], cycle_init[currentStep][FL_LEG][2]);
        currentState = state_moving;
      }
      break;
    case state_moving:
      legRL.updateLeg(elapsedMillis);
      legRR.updateLeg(elapsedMillis);
      legFR.updateLeg(elapsedMillis);
      legFL.updateLeg(elapsedMillis);
      if (!legRL.isMoving() && !legRR.isMoving() && !legFR.isMoving() && !legFL.isMoving()) {
        // finished move, get next
        currentState = state_next;
      }
      break;
    case state_waiting:
      // nothing yet
      break;
  }
  
  #endif
}
