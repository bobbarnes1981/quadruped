
#define CALIBRATION

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#ifdef CALIBRATION
#include "Calibration.h"
#endif

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define OSC_FREQ 26660574   // measured using arduino nano with pulseIn

// TODO: find pulse valid values for servos 0 and 180 (see below)

// HS645MG
// 553-2520μsec
// .100deg / us
#define HS645_SERVO_MIN 0.000900  //  900us
#define HS645_SERVO_MAX 0.002100  // 2100us

// HS422
#define HS422_SERVO_MIN 0.000900  //  900us
#define HS422_SERVO_MAX 0.002100  // 2100us

#ifdef CALIBRATION
Calibration calibration = Calibration(&pwm);
#endif

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
  pwm.setPWM( 0, 0, middle); delay(1000);
  pwm.setPWM( 1, 0, middle); delay(1000);
  pwm.setPWM( 2, 0, middle); delay(1000);
  
  pwm.setPWM( 4, 0, middle); delay(1000);
  pwm.setPWM( 5, 0, middle); delay(1000);
  pwm.setPWM( 6, 0, middle); delay(1000);

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
  pwm.setPWM( 1, 0, degToPulse( 90, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM( 2, 0, degToPulse(120, HS645_SERVO_MIN, HS645_SERVO_MAX));
  delay(1000);
  pwm.setPWM( 5, 0, degToPulse( 90, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM( 6, 0, degToPulse( 70, HS645_SERVO_MIN, HS645_SERVO_MAX));
  delay(1000);
  pwm.setPWM( 9, 0, degToPulse( 90, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM(10, 0, degToPulse(120, HS645_SERVO_MIN, HS645_SERVO_MAX));
  delay(1000);
  pwm.setPWM(13, 0, degToPulse( 90, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM(14, 0, degToPulse( 70, HS645_SERVO_MIN, HS645_SERVO_MAX));
  #endif
}
