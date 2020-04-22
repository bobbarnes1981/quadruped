
#define CALIBRATION

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#ifdef CALIBRATION
#include "Calibration.h"
#endif

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define OSC_FREQ 26660574   // measured using arduino nano with pulseIn

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

RobotServo servoRL_THIGH = RobotServo(&pwm, RL_THIGH, 550, 2450, 1100, 2450);
RobotServo servoRL_KNEE = RobotServo(&pwm, RL_KNEE, 700, 2600, 700, 2050);

RobotServo servoRR_THIGH = RobotServo(&pwm, RR_THIGH, 600, 2500, 600, 1950);
RobotServo servoRR_KNEE = RobotServo(&pwm, RR_KNEE, 450, 2350, 1000, 2350);

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
  
  pwm.setPWM(0, 0, middle); delay(1000);
  servoRL_THIGH.angle(0); delay(1000);
  servoRL_KNEE.angle(0); delay(1000);
  
  pwm.setPWM( 4, 0, middle); delay(1000);
  servoRR_THIGH.angle(0); delay(1000);
  servoRR_KNEE.angle(0); delay(1000);

  pwm.setPWM( 8, 0, middle); delay(1000);
  pwm.setPWM( 9, 0, middle); delay(1000);
  pwm.setPWM(10, 0, middle); delay(1000);
  
  pwm.setPWM(12, 0, middle); delay(1000);
  pwm.setPWM(13, 0, middle); delay(1000);
  pwm.setPWM(14, 0, middle); delay(1000);
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
  pwm.setPWM( 9, 0, degToPulse( 90, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM(10, 0, degToPulse(120, HS645_SERVO_MIN, HS645_SERVO_MAX));
  delay(1000);
  pwm.setPWM(13, 0, degToPulse( 90, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM(14, 0, degToPulse( 70, HS645_SERVO_MIN, HS645_SERVO_MAX));
  #endif
}
