
#define CALIBRATION

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#ifdef CALIBRATION
#include "Calibration.h"
#endif

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

#include "RobotServo.h"

// TODO: extend hip min/max to ~90degrees

RobotServo servoRL_HIP = RobotServo(&pwm, RL_HIP, 1000, 1950, 1000, 1950); // FIXME
RobotServo servoRL_THIGH = RobotServo(&pwm, RL_THIGH, 550, 2450, 1100, 2450);
RobotServo servoRL_KNEE = RobotServo(&pwm, RL_KNEE, 700, 2600, 700, 2050);

RobotServo servoRR_HIP = RobotServo(&pwm, RR_HIP, 1100, 2050, 1100, 2050); // FIXME
RobotServo servoRR_THIGH = RobotServo(&pwm, RR_THIGH, 600, 2500, 600, 1950);
RobotServo servoRR_KNEE = RobotServo(&pwm, RR_KNEE, 450, 2350, 1000, 2350);

RobotServo servoFR_HIP = RobotServo(&pwm, FR_HIP, 1050, 1950, 1050, 1950); // FIXME
RobotServo servoFR_THIGH = RobotServo(&pwm, FR_THIGH, 500, 2400, 1050, 2400);
RobotServo servoFR_KNEE = RobotServo(&pwm, FR_KNEE, 800, 2600, 800, 2150);

RobotServo servoFL_HIP = RobotServo(&pwm, FL_HIP, 1100, 2000, 1100, 2000); // FIXME
RobotServo servoFL_THIGH = RobotServo(&pwm, FL_THIGH, 600, 2500, 600, 1950);
RobotServo servoFL_KNEE = RobotServo(&pwm, FL_KNEE, 400, 2350, 1000, 2350);

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

  //hip, thigh, knee

  int middle = 1500 / (0.02 / 4096);
  
  servoRL_HIP.angle(0); delay(1000);
  servoRL_THIGH.angle(0); delay(1000);
  servoRL_KNEE.angle(0); delay(1000);
  
  servoRR_HIP.angle(0); delay(1000);
  servoRR_THIGH.angle(0); delay(1000);
  servoRR_KNEE.angle(0); delay(1000);

  servoFR_HIP.angle(0); delay(1000);
  servoFR_THIGH.angle(0); delay(1000);
  servoFR_KNEE.angle(0); delay(1000);
  
  servoFL_HIP.angle(0); delay(1000);
  servoFL_THIGH.angle(0); delay(1000);
  servoFL_KNEE.angle(0); delay(1000);
}

void loop() {
  #ifdef CALIBRATION
  calibration.processCommand();
  #else
  delay(1000);
  servoRL_THIGH.angle(0);
  servoRL_KNEE.angle(30);
  delay(1000);
  servoRR_THIGH.angle(0);
  servoRR_KNEE.angle(-30);
  delay(1000);
  servoFR_THIGH.angle(0);
  servoFR_KNEE.angle(30);
  delay(1000);
  servoFL_THIGH.angle(0);
  servoFL_KNEE.angle(-30);
  #endif
}
