// TODO: maybe replace classes with functions instead, to save on memory

#define LENGTH_FEMUR 59.0
#define LENGTH_TIBIA 122.0

#define BUTTON_A 7
#define BUTTON_B 8
#define BUTTON_C 9
#define LED_R 7
#define LED_G 8
#define LEG_Y 9
#define SPEAKER 5

#include <SoftwareSerial.h>

#include "RobotServo.h"
#include "RobotLeg.h"
#include "Quadruped.h"

RobotServo servoRL_HIP = RobotServo(RL_HIP, -45, 1, 0.001000, 0.001950, -45, 45);
RobotServo servoRL_THIGH = RobotServo(RL_THIGH, 0, 1, 0.001100, 0.002450, -38, 90);
RobotServo servoRL_KNEE = RobotServo(RL_KNEE, 90, -1, 0.000700, 0.002050, -90, 38);
RobotLeg legRL = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, -1, -1,
                   &servoRL_HIP,
                   &servoRL_THIGH,
                   &servoRL_KNEE
                 );

RobotServo servoRR_HIP = RobotServo(RR_HIP, 45, -1, 0.001100, 0.002050, -45, 45);
RobotServo servoRR_THIGH = RobotServo(RR_THIGH, 0, -1, 0.000600, 0.001950, -90, 38);
RobotServo servoRR_KNEE = RobotServo(RR_KNEE, -90, 1, 0.001000, 0.002350, -38, 90);
RobotLeg legRR = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, 1, -1,
                   &servoRR_HIP,
                   &servoRR_THIGH,
                   &servoRR_KNEE
                 );

RobotServo servoFR_HIP = RobotServo(FR_HIP, -45, 1, 0.001050, 0.001950, -45, 45);
RobotServo servoFR_THIGH = RobotServo(FR_THIGH, 0, 1, 0.001050, 0.002400, -38, 90);
RobotServo servoFR_KNEE = RobotServo(FR_KNEE, 90, -1, 0.000800, 0.002150, -90, 38);
RobotLeg legFR = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, 1, 1,
                   &servoFR_HIP,
                   &servoFR_THIGH,
                   &servoFR_KNEE
                 );

RobotServo servoFL_HIP = RobotServo(FL_HIP, 45, -1, 0.001100, 0.002000, -45, 45);
RobotServo servoFL_THIGH = RobotServo(FL_THIGH, 0, -1, 0.000650, 0.001950, -90, 38);
RobotServo servoFL_KNEE = RobotServo(FL_KNEE, -90, 1, 0.001000, 0.002350, -38, 90);
RobotLeg legFL = RobotLeg(
                   LENGTH_FEMUR, LENGTH_TIBIA, -1, 1,
                   &servoFL_HIP,
                   &servoFL_THIGH,
                   &servoFL_KNEE
                 );

Quadruped quadruped = Quadruped(&legRL, &legRR, &legFR, &legFL);

bool walking = false;
void setup() {
  Serial.begin(9600);

  delay(10);

  pinMode(BUTTON_A, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(BUTTON_C, INPUT);
  pinMode(SPEAKER, OUTPUT);

  quadruped.initialise();

  beep(128, 125);
  beep(0, 125);
  beep(128, 125);
}

void beep(int ton, int len) {
  analogWrite(SPEAKER, ton);
  delay(len);
  analogWrite(SPEAKER, 0);
}

enum States {
  state_start,
  state_input,
  state_walk_ready,
  state_walk_walking
};

States currentState = state_start;

void loop() {
  // TODO: move state machine inside class when other state machine has been deleted
  switch (currentState) {
    case state_start:
      {
        quadruped.stateStartup();
        currentState = state_input;
      }
      break;
    case state_input:
      {
        int a = digitalRead(BUTTON_A);
        if (!a) {
          beep(128, 125);
          quadruped.stateWalkReady();
          currentState = state_walk_ready;
        }
      }
      break;
    case state_walk_ready:
      {
        int a = digitalRead(BUTTON_A);
        if (!a) {
          beep(128, 125);
          beep(0, 62);
          beep(128, 125);
          quadruped.stateStartup();
          currentState = state_input;
        }
        int b = digitalRead(BUTTON_B);
        if (!b) {
          beep(128, 125);
          quadruped.stateWalking();
          currentState = state_walk_walking;
        }
      }
      break;
    case state_walk_walking:
      {
        int b = digitalRead(BUTTON_B);
        if (!b) {
          beep(128, 125);
          beep(0, 62);
          beep(128, 125);
          quadruped.stateWalkReady();
          currentState = state_walk_ready;
        }
      }
      break;
    default:
      // unhandled
      break;
  }
}
