#define trigPin 2
#define echoPin A0

void initRangeSensor(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int readDistanceInCm() {
  int average = 0;
  for (int i = 0; i < 3; i++) {
    average += readDistanceRaw();
    delay(200);
  }

  return average / 3;
}

int readDistanceRaw() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  noInterrupts();
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  interrupts();
  distance = (duration / 2) / 29.1;

  return (distance);
}

int findGapBearing() {
  attachServos();
  Serial.println("Finding farest distance in sight...");
  int highestDistance = 0;
  int bearing = -1;
  for (int i = 10; i < 170; i += 5) {
    pan(i);
    int readDistance = readDistanceInCm();
    if (readDistance > highestDistance) {
      highestDistance = readDistance;
      bearing = getPanValue();
    }
  }

  pan(bearing);
  delay(1000);
  pan(90);

  detachServos();

  return getBearingFromPanBearing(bearing);
}

int getBearingFromPanBearing(int panBearing) {
  //panBearing value between 0 (right) and 180 (left)
  //  0 --> 90
  // 90 --> 0
  //180 --> -90

  //Value between -90 and +90 degrees
  int deltaBearing = 0;
  if (panBearing > 90) {
    deltaBearing = (panBearing - 90) * -1;
  } else {
    deltaBearing = 90 - panBearing;
  }

  //deltaBearing is now to be added to overall bearing with the 360/turnaround
  int currentHeading = getHeading();

  return (currentHeading + panBearing) % 360;
}
