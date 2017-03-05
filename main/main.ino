#include <Servo.h>
/**
 * Initializations go here
 */
void setup() {
  Serial.begin(9600);
  initEngines(); //In File "motor": Make Motor Initializations
  initCompass(); //In File "compass": Make compass initializations
}

/**
 * The Main-Loop
 */
void loop() {
  
}


