#include <Servo.h>

#define DEFAULT_SERVO_DELAY 15

Servo panServo;
Servo tiltServo;

void attachServos() {
  tiltServo.attach(9);
  panServo.attach(10);
}

void detachServos() {
  tiltServo.detach();
  panServo.detach();
}

void demoPanTilt() {
  attachServos();

  lookUpSlow();
  lookDownSlow();
  centerVerticalSlow();

  lookLeftSlow();
  lookRightSlow();
  centerHorizontalSlow();

  detachServos();

}

void pan(int degree) {
  int currentPos = panServo.read();
  if (currentPos <= degree) {
    for (int pos = currentPos; pos <= degree; pos++) {
      panServo.write(pos);
      delay(DEFAULT_SERVO_DELAY);
    }
  } else {
    for (int pos = currentPos; pos > degree; pos--) {
      panServo.write(pos);
      delay(DEFAULT_SERVO_DELAY);
    }
  }
}

int getPanValue() {
  return panServo.read();
}

void lookLeftSlow() {
  int currentPos = panServo.read();
  for (int pos = currentPos; pos < 170; pos++) {
    panServo.write(pos);
    delay(DEFAULT_SERVO_DELAY);
  }
}

void lookRightSlow() {
  int currentPos = panServo.read();
  for (int pos = currentPos; pos > 10; pos--) {
    panServo.write(pos);
    delay(DEFAULT_SERVO_DELAY);
  }
}

void centerHorizontalSlow() {
  int currentPos = panServo.read();
  for (int pos = currentPos; pos < 90; pos++) {
    panServo.write(pos);
    delay(DEFAULT_SERVO_DELAY);
  }
}

void lookUpSlow() {
  int currentPos = tiltServo.read();
  for (int pos = currentPos; pos >= 10; pos--) {
    tiltServo.write(pos);
    delay(DEFAULT_SERVO_DELAY);
  }
}

void lookDownSlow() {
  int currentPos = tiltServo.read();
  for (int pos = currentPos; pos < 150; pos++) {
    tiltServo.write(pos);
    delay(DEFAULT_SERVO_DELAY);
  }
}

void centerVerticalSlow() {
  int currentPos = tiltServo.read();
  for (int pos = currentPos; pos > 88; pos--) {
    tiltServo.write(pos);
    delay(DEFAULT_SERVO_DELAY);
  }
}
