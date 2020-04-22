#include "Calibration.h"

Calibration::Calibration(Adafruit_PWMServoDriver *pwm) {
  this->pwm = pwm;
  for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
    this->servoMin[i] = DEFAULT_SERVO_MIN;
    this->servoMax[i] = DEFAULT_SERVO_MAX;
  }
}

Calibration::~Calibration() {
  
}

void Calibration::processCommand() {
  if (Serial.available()) {
    this->readCommand();
    switch (commandBuffer[0]) {
      case 'i':
        this->info();
        break;
      case 's':
        this->setServo();
        break;
      case 'n':
        this->setMin();
        break;
      case 'x':
        this->setMax();
        break;
      case 't':
        this->test();
        break;
      case 'g':
        this->goDegrees();
        break;
      case 'p':
        this->goPulse();
        break;
      default:
        Serial.println("servo s<n>, min n<n>, max x<n>, test t, go g<n>, pwm p<n>, info i");
        this->displayCommand();
        break;
    }
  }
}

void Calibration::readCommand() {
  int i = 0;
  int s;
  while ((s = Serial.read()) != LINE_FEED) {
    if (s != -1) {
      commandBuffer[i] = s;
      i++;
    }
  }
  commandBuffer[i] = 10;
}

void Calibration::displayCommand() {
  for (int i = 0; i < COMMAND_BUFFER_SIZE; i++) {
    if (commandBuffer[i] == LINE_FEED) {
      break;
    }
    Serial.print((char)commandBuffer[i]);
  }
  Serial.println();
}

int Calibration::readInt(int start) {
  int number = 0;
  for (int i = start; i < COMMAND_BUFFER_SIZE; i++) {
    if (commandBuffer[i] == LINE_FEED) {
      break;
    }
    number = number * 10;
    number += (commandBuffer[i]-48);
  }
  return number;
}

void Calibration::info() {
  Serial.print("servo:");
  Serial.println(this->currentServo);
  Serial.print("min:");
  Serial.println(this->servoMin[this->currentServo], 6);
  Serial.print("max:");
  Serial.println(this->servoMax[this->currentServo], 6);
}

void Calibration::setServo() {
  Serial.print("Set Servo: ");
  int number = readInt(1);
  if (number > 15) {
    number = 15;
  }
  this->currentServo = number;
  Serial.println(number);
}

void Calibration::setMin() {
  Serial.print("Set Min: ");
  int number = readInt(1);
  this->servoMin[this->currentServo] = number / 1000000.0;
  Serial.println(number);
  Serial.println(this->servoMin[this->currentServo], 6);
}

void Calibration::setMax() {
  Serial.print("Set Max: ");
  int number = readInt(1);
  this->servoMax[this->currentServo] = number / 1000000.0;
  Serial.println(number);
  Serial.println(this->servoMax[this->currentServo], 6);
}

void Calibration::test() {
  Serial.println("test");
  pwm->setPWM(this->currentServo, 0, this->degToPulse(0, this->servoMin[this->currentServo], this->servoMax[this->currentServo]));
  delay(250);
  for (int deg = 0; deg <= 180; deg += 10) {
    pwm->setPWM(this->currentServo, 0, this->degToPulse(deg, this->servoMin[this->currentServo], this->servoMax[this->currentServo]));
    Serial.println(deg);
    delay(20);
  }
  Serial.println("done");
}

void Calibration::goDegrees() {
  Serial.print("Go: ");
  int deg = readInt(1);
  Serial.println(deg);
  pwm->setPWM(this->currentServo, 0, this->degToPulse(deg, this->servoMin[this->currentServo], this->servoMax[this->currentServo]));
  Serial.println("done");
}

void Calibration::goPulse() {
  Serial.print("PWM: ");
  double pulse = readInt(1);
  Serial.println(pulse);
  pulse = pulse / 1000000.0;
  Serial.println(pulse, 6);
  pulse = pulse / ( 0.02 / 4096 );
  Serial.println(pulse);
  pwm->setPWM(this->currentServo, 0, pulse);
  Serial.println("done");
}

int Calibration::degToPulse(int deg, double minimum, double maximum) {
  double lo = minimum / ( SERVO_CYCLE / SERVO_STEP );
  double hi = maximum / ( SERVO_CYCLE / SERVO_STEP );
  return map(deg, 0, 180, lo, hi);
}
