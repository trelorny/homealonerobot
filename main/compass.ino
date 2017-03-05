#include <Wire.h>

#define Addr 0x1E
int BEARING_HYSTERESIS = 3;
int COURSE_CORRECTION_INTERVAL = 500;

void initCompass() {
  // Setup compass module
  Wire.begin();

  // Set operating mode to continuous
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}

int getHeading() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if (Wire.available() <= 6) {  // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  // If compass module lies flat on the ground with no tilt,
  // just x and y are needed for calculation
  float heading = atan2(-x, y) / 0.0174532925;
  if (heading < 0) heading += 360; // N=0/360, E=90, S=180, W=270
  return (int)heading;
}

