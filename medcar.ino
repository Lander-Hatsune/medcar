#include "motors.hpp"
#include "common.hpp"
#include "servo.hpp"
#include "oled.hpp"

void setup() {
  initServo();
  initOled();
  Serial1.begin(9600);
  while (!Serial1);
  Serial.begin(9600);
}

void loop() {
  setMotors();
  //disp("Pick 5 ;)");
}
