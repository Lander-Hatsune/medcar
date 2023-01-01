#pragma once

namespace ServoPin {
  const auto PWM = 9;
}

void initServo();
void setServo(float rad);
