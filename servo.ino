#include <Servo.h>
#include "servo.hpp"

Servo medbin;

void initServo() {
  medbin.attach(ServoPin::PWM);
}

void setServo(float rad=0) {
  medbin.write(rad * 180 / PI);
}
