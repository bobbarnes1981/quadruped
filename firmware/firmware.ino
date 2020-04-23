
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

RobotServo servoRL_HIP = RobotServo(&pwm, RL_HIP, 0.001000, 0.001950, 0.001000, 0.001950); // FIXME
RobotServo servoRL_THIGH = RobotServo(&pwm, RL_THIGH, 0.000550, 0.002450, 0.001100, 0.002450);
RobotServo servoRL_KNEE = RobotServo(&pwm, RL_KNEE, 0.000700, 0.002600, 0.000700, 0.002050);

RobotServo servoRR_HIP = RobotServo(&pwm, RR_HIP, 0.001100, 0.002050, 0.001100, 0.002050); // FIXME
RobotServo servoRR_THIGH = RobotServo(&pwm, RR_THIGH, 0.000600, 0.002500, 0.000600, 0.001950);
RobotServo servoRR_KNEE = RobotServo(&pwm, RR_KNEE, 0.000450, 0.002350, 0.001000, 0.002350);

RobotServo servoFR_HIP = RobotServo(&pwm, FR_HIP, 0.001050, 0.001950, 0.001050, 0.001950); // FIXME
RobotServo servoFR_THIGH = RobotServo(&pwm, FR_THIGH, 0.000500, 0.002400, 0.001050, 0.002400);
RobotServo servoFR_KNEE = RobotServo(&pwm, FR_KNEE, 0.000800, 0.002600, 0.000800, 0.002150);

RobotServo servoFL_HIP = RobotServo(&pwm, FL_HIP, 0.001100, 0.002000, 0.001100, 0.002000); // FIXME
RobotServo servoFL_THIGH = RobotServo(&pwm, FL_THIGH, 0.000650, 0.002500, 0.000600, 0.001950);
RobotServo servoFL_KNEE = RobotServo(&pwm, FL_KNEE, 0.000400, 0.002350, 0.001000, 0.002350);

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
  
  servoRL_HIP.angle(0); delay(500);
  servoRL_THIGH.angle(90); delay(500);
  servoRL_KNEE.angle(30); delay(500);
  
  servoRR_HIP.angle(0); delay(500);
  servoRR_THIGH.angle(-90); delay(500);
  servoRR_KNEE.angle(-30); delay(500);

  servoFR_HIP.angle(0); delay(500);
  servoFR_THIGH.angle(90); delay(500);
  servoFR_KNEE.angle(30); delay(500);
  
  servoFL_HIP.angle(0); delay(500);
  servoFL_THIGH.angle(-90); delay(500);
  servoFL_KNEE.angle(-30); delay(500);
}

void loop() {

  // debugging
  solve2DOF(150, -38);
  
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

double ab_length = 59;
double bc_length = 122;

void solve3DOF(double tx, double ty, double tz) {
  Serial.print("Servo0 angle: ");
  Serial.println(radToDeg(atan(ty / tx)));

  double AT = sqrt(pow(tx, 2) + pow(ty, 2));

  solve2DOF(AT, tz);
}

void solve2DOF(double tx, double ty) {
  double cx = tx;
  double cy = ty;

  double AC = sqrt(pow(cx, 2) + pow(cy, 2));
  double ac_angle = radToDeg(atan(cy / cx));

  //s=(AB+BC+AC)/2
  double s = (ab_length + bc_length + AC) / 2;

  //S=sqr(s*(s-AB)(s-BC)(s-AC))
  double S = sqrt(s * (s - ab_length) * (s - bc_length) * (s - AC));

  //A=asin(2S/(AB*AC))
  double A = radToDeg(asin((2 * S) / (ab_length * AC)));

  //B=asin(2S/(AB*BC))
  double B = radToDeg(asin((2 * S) / (ab_length * bc_length)));

  // Check if Hypoteneuse (AC) is big enough to mean triangle is obtuse
  // as rule of sines doesn't work on obtuse angles, could use rule of
  // cosines
  if (AC > sqrt(pow(ab_length, 2) + pow(bc_length, 2))) {
    B = 180 - B;
  }

  Serial.print("Servo1 angle: ");
  Serial.println(ac_angle + A);

  Serial.print("Servo2 angle: ");
  Serial.println(B);
}

double radToDeg(double rad) {
  return rad * (180 / PI);
}
