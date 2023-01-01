#pragma once

// motors' pins
namespace MotorPin {
  const auto EN_FL = 12;
  const auto EN_FR = 13;
  const auto IN_FL_0 = 29;
  const auto IN_FL_1 = 28;
  const auto IN_FR_0 = 27;
  const auto IN_FR_1 = 26;
  const auto EN_BL = 10;
  const auto EN_BR = 11;
  const auto IN_BL_0 = 32;
  const auto IN_BL_1 = 33;
  const auto IN_BR_0 = 30;
  const auto IN_BR_1 = 31;
}

namespace Speed {
  const auto MAX = 256;
  const auto MIN = -256;
  const auto RANGE = MAX - MIN;
}

void setMotors();
