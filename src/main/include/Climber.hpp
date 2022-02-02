#pragma once

#include "Constants.hpp"
#include "PID_CANSparkMax.hpp"

namespace Climber
{
    void init();
    void set(CLIMBER::POSITION position);
    void ButtonManager();
    void joystickControl(double);
    void joystickControlNoLimits(double val);
    void printStatus();
} // namespace Climber