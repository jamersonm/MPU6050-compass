#include <Arduino.h>
#include "Compass.h"

unsigned long timer_print = millis();

void setup() {
  Serial.begin(9600);
  configureCompass(); //initialize  the MPU 6050 sensor
}

void loop() {
  loopCompass(); // MPU sensor start getting yaw
  if((millis() - timer_print) > 5000) // after 5 segs
  {
    printCompass(); // print yaw
    timer_print = millis();
  }
}