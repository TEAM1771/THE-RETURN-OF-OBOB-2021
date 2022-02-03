#pragma once

#include <frc/GenericHID.h>

class JoystickButton
{
    frc::GenericHID& stick_;
    int const        button_;

public:
    JoystickButton(frc::GenericHID&, int const button);
    [[nodiscard]]      operator bool() const { return stick_.GetRawButton(button_); }
    [[nodiscard]] bool getRawButton() const;
    [[nodiscard]] bool getRawButtonPressed();
    [[nodiscard]] bool getRawButtonReleased();
};
