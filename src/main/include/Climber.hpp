#pragma once

/******************************************************************/
/*                        Public Constants                        */
/******************************************************************/
namespace CLIMBER
{
    typedef enum
    {
        DOWN = -163,
        UP = -968,
        ZERO = 0
    } POSITION;

} // namespace CLIMBER

/******************************************************************/
/*                  Public Function Declarations                  */
/******************************************************************/
namespace Climber
{
    void init();
    void set(CLIMBER::POSITION position);
    void ButtonManager();
    void joystickControl(double);
    void joystickControlNoLimits(double val);
    void printStatus();
} // namespace Climber