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

#define RL_HIP 0
#define RL_THIGH 1
#define RL_KNEE 2

#define RR_HIP 4
#define RR_THIGH 5
#define RR_KNEE 6

#define FR_HIP 8
#define FR_THIGH 9
#define FR_KNEE 10

#define FL_HIP 12
#define FL_THIGH 13
#define FL_KNEE 14

#define LENGTH_FEMUR 59.0
#define LENGTH_TIBIA 122.0

#include "RobotServo.h"
#include "RobotLeg.h"
#include "Quadruped.h"

// TODO: extend hip min/max to ~90degrees

RobotServo servoRL_HIP = RobotServo(&pwm, RL_HIP, 0, 1, 0.001000, 0.001950, 0.001000, 0.001950); // FIXME
RobotServo servoRL_THIGH = RobotServo(&pwm, RL_THIGH, 0, 1, 0.000550, 0.002450, 0.001100, 0.002450);
RobotServo servoRL_KNEE = RobotServo(&pwm, RL_KNEE, 90, -1, 0.000700, 0.002600, 0.000700, 0.002050);
RobotLeg legRL = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoRL_HIP,
  &servoRL_THIGH,
  &servoRL_KNEE
);

RobotServo servoRR_HIP = RobotServo(&pwm, RR_HIP, 0, 1, 0.001100, 0.002050, 0.001100, 0.002050); // FIXME
RobotServo servoRR_THIGH = RobotServo(&pwm, RR_THIGH,0, -1, 0.000600, 0.002500, 0.000600, 0.001950);
RobotServo servoRR_KNEE = RobotServo(&pwm, RR_KNEE, -90, 1, 0.000450, 0.002350, 0.001000, 0.002350);
RobotLeg legRR = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoRR_HIP,
  &servoRR_THIGH,
  &servoRR_KNEE
);

RobotServo servoFR_HIP = RobotServo(&pwm, FR_HIP, 0, 1, 0.001050, 0.001950, 0.001050, 0.001950); // FIXME
RobotServo servoFR_THIGH = RobotServo(&pwm, FR_THIGH, 0, 1, 0.000500, 0.002400, 0.001050, 0.002400);
RobotServo servoFR_KNEE = RobotServo(&pwm, FR_KNEE, 90, -1, 0.000800, 0.002600, 0.000800, 0.002150);
RobotLeg legFR = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoFR_HIP,
  &servoFR_THIGH,
  &servoFR_KNEE
);

RobotServo servoFL_HIP = RobotServo(&pwm, FL_HIP, 0, 1, 0.001100, 0.002000, 0.001100, 0.002000); // FIXME
RobotServo servoFL_THIGH = RobotServo(&pwm, FL_THIGH, 0, -1, 0.000650, 0.002500, 0.000600, 0.001950);
RobotServo servoFL_KNEE = RobotServo(&pwm, FL_KNEE, -90, 1, 0.000400, 0.002350, 0.001000, 0.002350);
RobotLeg legFL = RobotLeg(
  LENGTH_FEMUR, LENGTH_TIBIA,
  &servoFL_HIP,
  &servoFL_THIGH,
  &servoFL_KNEE
);

Quadruped quadruped = Quadruped(&legRL, &legRR, &legFR, &legFL);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  pwm.begin();
  // In theory the internal oscillator is 25MHz but it really isn't
  // that precise. You can 'calibrate' by tweaking this number till
  // you get the frequency you're expecting!
  pwm.setOscillatorFrequency(OSC_FREQ);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  
  legRL.moveLeg(150, 0, 0);
  legRR.moveLeg(150, 0, 0);
  legFR.moveLeg(150, 0, 0);
  legFL.moveLeg(150, 0, 0);

  delay(2000);

  legRL.setTarget(120, 0, 0);
  legRR.setTarget(120, 0, 0);
  legFR.setTarget(120, 0, 0);
  legFL.setTarget(120, 0, 0);
}

unsigned long lastMillis = 0;

void loop() {
  #ifdef CALIBRATION
  calibration.processCommand();
  #else

  unsigned long currentMillis = millis();
  unsigned long elapsedMillis = currentMillis - lastMillis;
  lastMillis = currentMillis;

  legRL.updateLeg(elapsedMillis);
  legRR.updateLeg(elapsedMillis);
  legFR.updateLeg(elapsedMillis);
  legFL.updateLeg(elapsedMillis);
  
  #endif
}

void testing() {
  // touch the ground 15cm from body
  legRL.moveLeg(150, 0, -38);
  legRR.moveLeg(150, 0, -38);
  legFR.moveLeg(150, 0, -38);
  legFL.moveLeg(150, 0, -38);
  delay(1000);
  // lift legs from the ground
  legRL.moveLeg(150, 0, 0);
  legRR.moveLeg(150, 0, 0);
  legFR.moveLeg(150, 0, 0);
  legFL.moveLeg(150, 0, 0);
  delay(1000);
  // move legs in and down
  legRL.moveLeg(120, 0, -20);
  legRR.moveLeg(120, 0, -20);
  legFR.moveLeg(120, 0, -20);
  legFL.moveLeg(120, 0, -20);
  delay(1000);
  // lift body 1cm from the ground
  legRL.moveLeg(120, 0, -50);
  legRR.moveLeg(120, 0, -50);
  legFR.moveLeg(120, 0, -50);
  legFL.moveLeg(120, 0, -50);
  delay(5000);
  // lift legs back off the ground
  legRL.moveLeg(120, 0, -20);
  legRR.moveLeg(120, 0, -20);
  legFR.moveLeg(120, 0, -20);
  legFL.moveLeg(120, 0, -20);
  delay(1000);
}
