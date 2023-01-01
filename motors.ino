#include <L298NX2.h>
#include "motors.hpp"

// https://github.com/AndreaLombardo/L298N
/* motors
   [[front-left, back-left],
    [front-right, back-right]]
*/
L298N* motors[2][2] = {
  {new L298N(MotorPin::EN_FL, MotorPin::IN_FL_0, MotorPin::IN_FL_1),
   new L298N(MotorPin::EN_BL, MotorPin::IN_BL_0, MotorPin::IN_BL_1)},
  {new L298N(MotorPin::EN_FR, MotorPin::IN_FR_0, MotorPin::IN_FR_1),
   new L298N(MotorPin::EN_BR, MotorPin::IN_BR_0, MotorPin::IN_BR_1)}
};

int speedClip(int x) {
  return min(max(x, Speed::MIN + 1), Speed::MAX - 1);
}

void setMotors() {
  int ls = 0, rs = 0;
  if (Serial1.available()) {
    auto data = Serial1.readStringUntil('#').toInt();

    float radius = float(data % 10000) / 1000;
    float angle = float(int(data / 10000)) / 360 * 2 * PI;

    /*
      linear inbetween:
                  (MAX, MAX)
                      ^ 
                      |
      (-MAX, MAX) <---+---> (MAX, -MAX)
                      |
                      v
                 (-MAX, -MAX)
     */
    if (angle >= 0 && angle < PI / 2) {
      ls = Speed::MAX;
      rs = -Speed::MAX + Speed::RANGE * angle / (PI / 2);
    } else if (angle >= PI / 2 && angle < PI) {
      ls = Speed::MAX - Speed::RANGE * (angle - PI / 2) / (PI / 2);
      rs = Speed::MAX;
    } else if (angle >= PI && angle < PI * 3 / 2) {
      ls = -Speed::MAX;
      rs = Speed::MAX - Speed::RANGE * (angle - PI) / (PI / 2);
    } else { // angle >= PI * 3 / 2 && angle < 2 * PI
      ls = -Speed::MAX + Speed::RANGE * (angle - PI * 3 / 2) / (PI / 2);
      rs = -Speed::MAX;
    }

    ls *= radius;
    rs *= radius;
    ls = speedClip(ls);
    rs = speedClip(rs);

    /* Serial.println("ls, rs:"); */
    /* Serial.println(ls); */
    /* Serial.println(rs); */

    for (auto lm: motors[0]) { // left motors
      lm->setSpeed(abs(ls));
      ls > 0 ? lm->forward() : lm->backward();
      if (ls == 0) lm->stop();
    }
    for (auto rm: motors[1]) { // right motors
      rm->setSpeed(abs(rs));
      rs > 0? rm->forward() : rm->backward();
      if (rs == 0) rm->stop();
    }

    /* Serial.println("left motors:"); */
    /* Serial.println(motors[0][0]->getSpeed()); */
    /* Serial.println(motors[0][0]->getDirection()); */
    /* Serial.println(motors[0][1]->getSpeed()); */
    /* Serial.println(motors[0][1]->getDirection()); */
    /* Serial.println("right motors:"); */
    /* Serial.println(motors[1][0]->getSpeed()); */
    /* Serial.println(motors[1][0]->getDirection()); */
    /* Serial.println(motors[1][1]->getSpeed()); */
    /* Serial.println(motors[1][1]->getDirection()); */
    /* Serial.println(); */
  }
}

