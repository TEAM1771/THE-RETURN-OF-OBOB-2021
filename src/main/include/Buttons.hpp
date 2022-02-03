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
    inline frc::Joystick JOY1{0}, JOY2{1};

    namespace CLIMBER
    {
        inline JoystickButton RAISE{BUTTON::JOY2, 11};
        inline JoystickButton LOWER{BUTTON::JOY1, 6};
    } // namespace CLIMBER
} // namespace BUTTON