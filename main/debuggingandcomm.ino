#include <SoftwareSerial.h>

#define rxPin A2
#define txPin A3

SoftwareSerial btSerial(rxPin, txPin);
String btData;

void initComm(){
  btSerial.begin(9600);
  btSerial.println("bluetooth available");
}

void fetchCommand() {
    if (btSerial.available()){
      btData = btSerial.readString();
      printToSerial("Got message: " + btData);
    }
}


void printToSerial(String msg) {
  Serial.println(millis() + msg);
  btSerial.println(millis() + msg);
}
