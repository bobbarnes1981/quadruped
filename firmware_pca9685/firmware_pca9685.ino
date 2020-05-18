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

unsigned long lastMillis = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  pwm.begin();
  pwm.setOscillatorFrequency(OSC_FREQ);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  quadruped.initialise();

  lastMillis = millis();
}

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
    //Serial.println(s);
    if (s == 's') {
      quadruped.startup();
    }
    if (s == 'k') {
      quadruped.kinematics();
    }
    if (s == 'w') {
      quadruped.walk();
    }
    if (s == 'u') {
      quadruped.alterOffsets(0, 0, -10);
    }
    if (s == 'd') {
      quadruped.alterOffsets(0, 0, 10);
    }
    if (s == 'l') {
      quadruped.alterOffsets(10, 0, 0);
    }
    if (s == 'r') {
      quadruped.alterOffsets(-10, 0, 0);
    }
    if (s == 'f') {
      quadruped.alterOffsets(0, -10, 0);
    }
    if (s == 'b') {
      quadruped.alterOffsets(0, 10, 0);
    }
  }

  quadruped.updateQuadruped(elapsedMillis);

#endif
}
