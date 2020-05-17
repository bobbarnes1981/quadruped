#include "config.h"
#include "robotservo.h"
#include "robotleg.h"
#include "quadruped.h"

// TODO: use config values

RobotServo servoRL_HIP = RobotServo(RR_L_HIP_SERVO, -45, 1, 1000, 1950, -45, 45);
RobotServo servoRL_THIGH = RobotServo(RR_L_THIGH_SERVO, 0, 1, 1100, 2450, -38, 90);
RobotServo servoRL_KNEE = RobotServo(RR_L_KNEE_SERVO, 90, -1, 700, 2050, -90, 38);
RobotLeg legRL = RobotLeg(LENGTH_FEMUR, LENGTH_TIBIA, -1, -1, &servoRL_HIP, &servoRL_THIGH, &servoRL_KNEE);

RobotServo servoRR_HIP = RobotServo(RR_R_HIP_SERVO, 45, -1, 1100, 2050, -45, 45);
RobotServo servoRR_THIGH = RobotServo(RR_R_THIGH_SERVO, 0, -1, 600, 1950, -90, 38);
RobotServo servoRR_KNEE = RobotServo(RR_R_KNEE_SERVO, -90, 1, 1000, 2350, -38, 90);
RobotLeg legRR = RobotLeg(LENGTH_FEMUR, LENGTH_TIBIA, 1, -1, &servoRR_HIP, &servoRR_THIGH, &servoRR_KNEE);

RobotServo servoFR_HIP = RobotServo(FT_R_HIP_SERVO, -45, 1, 1050, 1950, -45, 45);
RobotServo servoFR_THIGH = RobotServo(FT_R_THIGH_SERVO, 0, 1, 1050, 2400, -38, 90);
RobotServo servoFR_KNEE = RobotServo(FT_R_KNEE_SERVO, 90, -1, 800, 2150, -90, 38);
RobotLeg legFR = RobotLeg(LENGTH_FEMUR, LENGTH_TIBIA, 1, 1, &servoFR_HIP, &servoFR_THIGH, &servoFR_KNEE);

RobotServo servoFL_HIP = RobotServo(FT_L_HIP_SERVO, 45, -1, 1100, 2000, -45, 45);
RobotServo servoFL_THIGH = RobotServo(FT_L_THIGH_SERVO, 0, -1, 650, 1950, -90, 38);
RobotServo servoFL_KNEE = RobotServo(FT_L_KNEE_SERVO, -90, 1, 1000, 2350, -38, 90);
RobotLeg legFL = RobotLeg(LENGTH_FEMUR, LENGTH_TIBIA, -1, 1, &servoFL_HIP, &servoFL_THIGH, &servoFL_KNEE);

Quadruped quadruped = Quadruped(&legRL, &legRR, &legFR, &legFL);

enum state {
  start,
  input,
  walk_init,
  walk_waiting,
  walk_step,
  waiting
};
state currentState = start;

#define BUTTON_A 7
#define BUTTON_B 8
#define BUTTON_C 9
#define LED_R 7
#define LED_G 8
#define LEG_Y 9
#define SPEAKER 5

void setup() {
  pinMode(BUTTON_A, INPUT);
  pinMode(SPEAKER, OUTPUT);
  
  Serial.begin(9600);

  quadruped.initialise();

  delay(1000);
  
  analogWrite(SPEAKER, 128);
  delay(125);
  analogWrite(SPEAKER, 0);
}

void loop() {
  switch(currentState) {
    case start:
      {
        quadruped.waiting();
        currentState = input;
      }
      break;
    case input:
      {
        int notPressed = digitalRead(BUTTON_A);
        if (!notPressed) {
          analogWrite(SPEAKER, 128);
          delay(250);
          analogWrite(SPEAKER, 0);
          currentState = walk_init;
        }
      }
      break;
    case walk_init:
      {
        quadruped.walkInit();
        currentState = walk_waiting;
      }
      break;
    case walk_waiting:
      {
        int notPressed = digitalRead(BUTTON_A);
        if (!notPressed) {
          analogWrite(SPEAKER, 128);
          delay(250);
          analogWrite(SPEAKER, 0);
          currentState = start;
        }
        notPressed = digitalRead(BUTTON_B);
        if (!notPressed) {
          analogWrite(SPEAKER, 128);
          delay(250);
          analogWrite(SPEAKER, 0);
          currentState = walk_step;
        }
      }
      break;
    case walk_step:
      {
        quadruped.walk();
        currentState = walk_waiting;
      }
      break;
    case waiting:
      {
        // nothing
      }
      break;
  }
}
