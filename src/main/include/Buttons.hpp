#pragma once

#include <frc/Joystick.h>

class JoystickButton
{
    /******************************************************************/
    /*                  Private Variable Declarations                 */
    /******************************************************************/
    frc::GenericHID &stick_;
    int const button_;

public:
    /******************************************************************/
    /*                  Public Function Declarations                  */
    /******************************************************************/
    JoystickButton(frc::GenericHID &, int const button);
    [[nodiscard]] operator bool() const { return stick_.GetRawButton(button_); }
    [[nodiscard]] bool getRawButton() const;
    [[nodiscard]] bool getRawButtonPressed();
    [[nodiscard]] bool getRawButtonReleased();
};

/******************************************************************/
/*                        Public Constants                        */
/******************************************************************/
namespace BUTTON
{
    inline frc::Joystick JOY1{0};

    inline JoystickButton TRIANGLE{BUTTON::JOY1, 4};
    inline JoystickButton CIRCLE{BUTTON::JOY1, 3};
    inline JoystickButton SQUARE{BUTTON::JOY1, 1};
    inline JoystickButton X{BUTTON::JOY1, 2};
} // namespace BUTTON