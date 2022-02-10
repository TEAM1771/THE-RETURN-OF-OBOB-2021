#pragma once

#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>

//Drivetrain is a class to avoid issues with early initialization

/******************************************************************/
/*                       Private Constants                        */
/******************************************************************/
namespace SOLENOID
{
    constexpr int PORT = 0;

    constexpr bool SHIFT_UP = true;
    constexpr bool SHIFT_DOWN = !SHIFT_UP;
    constexpr bool DEFAULT = SHIFT_DOWN;

    constexpr int SHIFT_UP_VOLTAGE = 8;
    constexpr int SHIFT_DOWN_VOLTAGE = 2;

    constexpr int SHIFT_UP_CURRENT = 2;
    constexpr int SHIFT_DOWN_CURRENT = 20;

} // namespace SOLENOID

class Drivetrain
{
private:
    /******************************************************************/
    /*                        Private Variables                       */
    /******************************************************************/

    WPI_TalonSRX fl{2};
    WPI_TalonSRX bl{17};
    WPI_TalonSRX fr{4};
    WPI_TalonSRX br{5};

    /* frc::Solenoid shifter{SOLENOID::PORT};

    bool shift_status = SOLENOID::DEFAULT;

    bool can_shift = false;
    */

public:
    /******************************************************************/
    /*                  Public Function Declarations                  */
    /******************************************************************/
    Drivetrain();

    void tank(double lrate, double rrate);

    /*
    void shift(bool toshift);
    void shift();
    */

    double getVoltage();
    double getCurrent();

    void printStatus();
}; // namespace Drivetrain