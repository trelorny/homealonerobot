#include <Servo.h>
/**
 * Initializations go here
 */
void setup() {
  Serial.begin(9600);
  initEngines(); //In File "motor": Make Motor Initializations
  initCompass(); //In File "compass": Make compass initializations
  initRangeSensor();
}

int BEARING = 0; //We start facing north (more or less)
/**
 * The Main-Loop
 */
void loop() {
  printToSerial("Executing Main Loop");

  //Go forward until obstacle is detected
  int distanceRead = readDistanceInCm();
  if (distanceRead < 30) {
    printToSerial("Obstacle detected - turning to");
    //Search for open gap and turn to that bearing using compassmodule
    BEARING = findGapBearing();
    printToSerial((String)BEARING);
    printToSerial("degrees");
  }

  holdCourse(BEARING);
  delay(200);
  fetchCommand();
}


