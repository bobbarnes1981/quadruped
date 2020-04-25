#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_CYCLE 0.02    // 50Hz is 0.02s cycle
#define SERVO_STEP 4096     // 4096 descrete steps

#define DEFAULT_SERVO_MIN 0.000900 //  900us
#define DEFAULT_SERVO_MAX 0.002100 // 2100us

#define NUMBER_OF_SERVOS 16
#define COMMAND_BUFFER_SIZE 15
#define LINE_FEED 10

class Calibration {
  private:
    Adafruit_PWMServoDriver *pwm;
    int currentServo = 0;
    double servoMin[NUMBER_OF_SERVOS];
    double servoMax[NUMBER_OF_SERVOS];
    int commandBuffer[COMMAND_BUFFER_SIZE];
  public:
    Calibration(Adafruit_PWMServoDriver *pwm);
    void processCommand();
    void readCommand();
    void displayCommand();
    void info();
    void setServo();
    void setMin();
    void setMax();
    void test();
    void goDegrees();
    void goPulse();
    int readInt(int start);
    int degToPulse(int deg, double minimum, double maximum);
    ~Calibration();
};

#endif
