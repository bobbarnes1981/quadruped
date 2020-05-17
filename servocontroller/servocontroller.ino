#include <Servo.h>

#define SERVO_OFFSET 2
#define SERVOS_MIN 0
#define SERVOS_MAX 12
#define PULSE_MIN 500
#define PULSE_MAX 2500
#define TIME_MIN 1
#define TIME_MAX 65535
#define SPEED_MIN 1
#define SPEED_MAX 65535

Servo servos[SERVOS_MAX];
int speeds[SERVOS_MAX];
double currents[SERVOS_MAX];
double targets[SERVOS_MAX];
double maxs[SERVOS_MAX];
double mins[SERVOS_MAX];

#define INTBUFFER 5
#define ASCII0 48
#define ASCII9 57

unsigned long previousMillis;

void setup() {
  Serial.begin(9600);
  
  for (int i = 0; i < SERVOS_MAX; i++) {
    //servos[i].attach(i+SERVO_OFFSET);
    speeds[i] = -1;
    currents[i] = -1;
    targets[i] = -1;
    maxs[i] = 2500;
    mins[i] = 500;
  }

  previousMillis = millis();
}

int bufferContent[255];
int bufferLength = 0;
bool bufferComplete = false;

void loop() {
  // read buffer
  while (!bufferComplete && Serial.available()) {
    bufferContent[bufferLength] = Serial.read();
    if (bufferContent[bufferLength] == '\r') {
      bufferComplete = true;
    }
    bufferLength++;
  }

  // process complete buffer
  if (bufferComplete) {
    readCommand();
    bufferLength = 0;
    bufferComplete = false;
  }

  // update servos
  unsigned long currentMillis = millis();
  updateServos(currentMillis - previousMillis);
  previousMillis = currentMillis;
}

void updateServos(int elapsedMillis) {
  for (int i = 0; i < SERVOS_MAX; i++) {
    if (currents[i] != targets[i]) {
      if (speeds[i] != -1) {
        double distance = currents[i] - targets[i];
        double movement = (speeds[i] * elapsedMillis) / 1000.0;
        int dir = distance > 0 ? -1 : 1;
        double next;
        if (abs(distance) < movement) {
          next = targets[i];
        } else {
          next = currents[i] + (movement * dir);
        }
        if (next < mins[i]) {
          next = mins[i];
        }
        if (next > maxs[i]) {
          next = maxs[i];
        }
        currents[i] = next;
      } else {
        currents[i] = targets[i];
      }

      if (currents[i] != -1) {
        servos[i].writeMicroseconds(currents[i]);
        if (!servos[i].attached()) {
          servos[i].attach(i+SERVO_OFFSET);
        }
      }
    }
  }
}

int offset;

void readCommand() {
  #ifdef DEBUG
  for (int i = 0; i < bufferLength; i++) {
    Serial.print((char)bufferContent[i]);
  }
  Serial.println();
  #endif  
  offset = 0;
  int c = -1;
  int p = -1;
  int s = -1;
  int t = -1;
  if (bufferContent[offset] == (int)'#') {
    offset++;
    c = readInt();
    if (bufferContent[offset] == (int)'P') {
      offset++;
      p = readInt();
      if (bufferContent[offset] == (int)'S') {
        offset++;
        s = readInt();
      }
      if (bufferContent[offset] == (int)'T') {
        offset++;
        t = readInt();
      }
    }
    #ifdef DEBUG
    Serial.print("channel: ");
    Serial.println(c);
    Serial.print("pulse: ");
    Serial.println(p);
    Serial.print("speed: ");
    Serial.println(s);
    Serial.print("time: ");
    Serial.println(t);
    #endif
    if (c >= SERVOS_MIN && c < SERVOS_MAX) {
      if ((s >= SPEED_MIN && s <= SPEED_MAX) || s == -1) {
        speeds[c] = s;
      }
      if ((t >= TIME_MIN && t <= TIME_MAX) || t == -1) {
        // TODO: validate this!
        // milliseconds per second
        speeds[c] = abs(currents[c] - p) / t * 1000;
      }
      if (p >= PULSE_MIN && p <= PULSE_MAX) {
        targets[c] = p;
      }
    }
  } else if (bufferContent[offset] == (int)'Q') {
    offset++;
    if (bufferContent[offset] == (int)'P') {
      c = readInt();
      if (c >= SERVOS_MIN && c < SERVOS_MAX) {
        Serial.print(currents[c] / 10);
        Serial.print("\r");
      }
    } else {
      // assume <CR>
      bool moving = false;
      for (int i = 0; i < SERVOS_MAX; i++) {
        if (targets[i] != currents[i]) {
          moving = true;
          break;
        }
      }
      if (moving) {
        Serial.print("+\r");
      } else {
        Serial.print(".\r");
      }
    }
  }
}

int readInt() {
  int b[INTBUFFER];
  for (int i = 0; i < INTBUFFER; i++) {
    b[i] = bufferContent[offset];
    if (b[i] < ASCII0 || b[i] > ASCII9) {
      int x = 0;
      int p = 1;
      for (int j = 0; j < i; j++) {
        x += (b[i-(j+1)]-ASCII0) * p;
        p *= 10;
      }
      return x;
    }
    offset++;
  }
  // read full buffer, fail.
  return -1;
}
