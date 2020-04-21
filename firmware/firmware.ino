#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50       // Analog servos run at ~50 Hz updates
#define SERVO_CYCLE 0.02    // 50Hz is 0.02s cycle
#define SERVO_STEP 4096     // 4096 descrete steps

// TODO: calibrate servos separately?

// HS311
#define HS311_SERVO_MIN 0.000600  //  600us
#define HS311_SERVO_MAX 0.002300  // 2300us

// HS645MG
#define HS645_SERVO_MIN 0.000900  //  900us
#define HS645_SERVO_MAX 0.002100  // 2100us

// HS422
#define HS422_SERVO_MIN 0.000600  //  600us
#define HS422_SERVO_MAX 0.002100  // 2100us

// Calibration 
#define BUFFER_SIZE 15
#define LF 10

bool calibrationMode = true;

int cal_servo = 0;
double cal_min = 0.000900;
double cal_max = 0.002100;

int commandBuffer[BUFFER_SIZE];

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  pwm.begin();
  // In theory the internal oscillator is 25MHz but it really isn't
  // that precise. You can 'calibrate' by tweaking this number till
  // you get the frequency you're expecting!
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  //hip, thigh, knee

  pwm.setPWM( 0, 0, degToPulse( 90, HS422_SERVO_MIN, HS422_SERVO_MAX));
  pwm.setPWM( 1, 0, degToPulse(180, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM( 2, 0, degToPulse(160, HS645_SERVO_MIN, HS645_SERVO_MAX));
  
  pwm.setPWM( 4, 0, degToPulse( 90, HS422_SERVO_MIN, HS422_SERVO_MAX));
  pwm.setPWM( 5, 0, degToPulse(  0, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM( 6, 0, degToPulse( 20, HS645_SERVO_MIN, HS645_SERVO_MAX));

  pwm.setPWM( 8, 0, degToPulse( 90, HS422_SERVO_MIN, HS422_SERVO_MAX));
  pwm.setPWM( 9, 0, degToPulse(180, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM(10, 0, degToPulse(160, HS645_SERVO_MIN, HS645_SERVO_MAX));
  
  pwm.setPWM(12, 0, degToPulse( 90, HS422_SERVO_MIN, HS422_SERVO_MAX));
  pwm.setPWM(13, 0, degToPulse(  0, HS645_SERVO_MIN, HS645_SERVO_MAX));
  pwm.setPWM(14, 0, degToPulse( 20, HS645_SERVO_MIN, HS645_SERVO_MAX));

}

int degToPulse(int deg, double minimum, double maximum) {
  double lo = minimum / ( SERVO_CYCLE / SERVO_STEP );
  double hi = maximum / ( SERVO_CYCLE / SERVO_STEP );
  return map(deg, 0, 180, lo, hi);
}

void loop() {
  if (calibrationMode) {
    calibration();
  } else {
    execution();
  }
}

void readCommand() {
  int i = 0;
  int s;
  while ((s = Serial.read()) != LF) {
    if (s != -1) {
      commandBuffer[i] = s;
      i++;
    }
  }
  commandBuffer[i] = 10;
}

void displayCommand() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (commandBuffer[i] == LF) {
      break;
    }
    Serial.print((char)commandBuffer[i]);
  }
  Serial.println();
}

int readInt(int start) {
  int number = 0;
  for (int i = start; i < BUFFER_SIZE; i++) {
    if (commandBuffer[i] == LF) {
      break;
    }
    number = number * 10;
    number += (commandBuffer[i]-48);
  }
  return number;
}

void calibration() {
  if (Serial.available()) {
    readCommand();
    switch (commandBuffer[0]) {
      case 'i':
        info();
        break;
      case 's':
        setServo();
        break;
      case 'n':
        setMin();
        break;
      case 'x':
        setMax();
        break;
      case 't':
        test();
        break;
      case 'g':
        go();
        break;
      default:
        Serial.println("servo s<n>, min n<n>, max x<n>, test t, go g<n>, info i");
        displayCommand();
        break;
    }
  }
}

void info() {
  Serial.print("servo:");
  Serial.println(cal_servo);
  Serial.print("min:");
  Serial.println(cal_min, 6);
  Serial.print("max:");
  Serial.println(cal_max, 6);
}

void setServo() {
  Serial.print("Set Servo: ");
  int number = readInt(1);
  if (number > 15) {
    number = 15;
  }
  cal_servo = number;
  Serial.println(number);
}

void setMin() {
  Serial.print("Set Min: ");
  int number = readInt(1);
  cal_min = number / 1000000.0;
  Serial.println(number);
  Serial.println(cal_min, 6);
}

void setMax() {
  Serial.print("Set Max: ");
  int number = readInt(1);
  cal_max = number / 1000000.0;
  Serial.println(number);
  Serial.println(cal_max, 6);
}

void test() {
  Serial.println("test");
  pwm.setPWM(cal_servo, 0, degToPulse(0, cal_min, cal_max));
  delay(250);
  for (int deg = 0; deg <= 180; deg += 10) {
    pwm.setPWM(cal_servo, 0, degToPulse(deg, cal_min, cal_max));
    Serial.println(deg);
    delay(20);
  }
  Serial.println("done");
}

void go() {
  Serial.print("Go: ");
  int deg = readInt(1);
  Serial.println(deg);
  pwm.setPWM(cal_servo, 0, degToPulse(deg, cal_min, cal_max));
  Serial.println("done");
}

void execution() {
  
}
