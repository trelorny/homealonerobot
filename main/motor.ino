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


/***************** MOTION CONTROL END ************/
