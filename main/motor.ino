#include <AFMotor.h>

/**** MOTORS ****/
#define SPEED 75
#define SPEED2 150
// DC motor on M1 (Rear left)
AF_DCMotor RL(1);
// DC motor on M2 (Rear Right)
AF_DCMotor RR(2);
// DC motor on M3 (Front Right)
AF_DCMotor FR(3);
// DC motor on M4 (Front Left)
AF_DCMotor FL(4);

/***************** MOTION CONTROL BEGIN ************/
void forward() {
  FR.run(FORWARD);
  FL.run(FORWARD);
  RR.run(FORWARD);
  RL.run(FORWARD);
}

void backward(){
  FR.run(BACKWARD);
  RR.run(BACKWARD);
  FL.run(BACKWARD);
  RL.run(BACKWARD);
}

void turnRight() {
  FL.run(FORWARD);
  RL.run(FORWARD);
  FR.run(BACKWARD);
  RR.run(BACKWARD);
}

void turnLeft() {
  FR.run(FORWARD);
  RR.run(FORWARD);
  FL.run(BACKWARD);
  RL.run(BACKWARD);
}

void initEngines() {
  // turn on motors
  FR.setSpeed(SPEED2);
  FL.setSpeed(SPEED2);
  RR.setSpeed(SPEED);
  RL.setSpeed(SPEED);
}

void stopEngines() {
  FR.run(RELEASE);
  FL.run(RELEASE);
  RR.run(RELEASE);
  RL.run(RELEASE);
}

/**
 * Turning right means: Degrees increase until 359, after that degrees start from 0
 */
void turnRight(int deltaBearing) {

  int currBearing = getHeading(); 
  int targetBearing = (currBearing + deltaBearing) % 360;

  boolean hasToMoveOver360 = targetBearing < currBearing; 
  boolean movedOver360 = !(targetBearing < currBearing);
  printToSerial("Turing right to " + (String) targetBearing + ", will move over 360: " + (String) hasToMoveOver360);
  while ((hasToMoveOver360 && !movedOver360) || currBearing < targetBearing) {
    currBearing = getHeading();
    if(hasToMoveOver360){
      movedOver360 = currBearing < BEARING_HYSTERESIS;
      if(hasToMoveOver360){
        printToSerial("Moved over 360 at bearing " + (String) currBearing); //Most likely currBearing is between 0 and maybe 2, depends on the turning speed
        hasToMoveOver360 = false;
      }
    }
    turnRight();
    delay(COURSE_CORRECTION_INTERVAL);
  }
  printToSerial("Right turn complete. Bearing is now " + (String) currBearing);
}


/**
 * Turning left means: Degrees decreases until 0, after that degrees start from 359
 */
void turnLeft(int deltaBearing) {

  int currBearing = getHeading(); 
  int targetBearing = currBearing - deltaBearing; //Always less than 360 as we are substracting deltaBearing
  printToSerial("Turing left to " + (String) targetBearing);
  while (currBearing > targetBearing) {
    currBearing = getHeading();
    turnLeft();
    delay(COURSE_CORRECTION_INTERVAL);
  }
  printToSerial("Left turn complete. Bearing is now " + (String) currBearing);
}



void holdCourse(int bearing) {
  printToSerial("Course set to " + (String) bearing);
  int currBearing = getHeading();
  if (currBearing < bearing - BEARING_HYSTERESIS) { //We are off course - move to
    stopEngines();
    turnLeft();
  } else if (bearing + BEARING_HYSTERESIS < currBearing) {
    stopEngines();
    turnRight();
  } else {
    forward();
  }
  delay(COURSE_CORRECTION_INTERVAL);
}
