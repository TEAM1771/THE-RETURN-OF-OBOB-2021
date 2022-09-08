#include <DriveTrain.hpp>

#include <frc/smartdashboard/SmartDashboard.h>

#include <math.h>

/******************************************************************/
/*                   Public Function Definitions                  */
/******************************************************************/

Drivetrain::Drivetrain()
{
    // shifter.Set(SOLENOID::DEFAULT);

    auto const talon_config = []() {
        TalonSRXConfiguration talon_config;
        talon_config.closedloopRamp = .2; // Sets a nice voltage curve to make the robot less jerky
        return talon_config;
    }();

    // Sets the configuration on each motor
    fl.ConfigAllSettings(talon_config);
    bl.ConfigAllSettings(talon_config);
    fr.ConfigAllSettings(talon_config);
    br.ConfigAllSettings(talon_config);
}

[[nodiscard]] double Drivetrain::getVoltage()
{
    // Takes the absolute value of the average
    return std::abs((fl.GetMotorOutputVoltage() - fr.GetMotorOutputVoltage()) / 2.0);
}

[[nodiscard]] double Drivetrain::getCurrent()
{
    // Takes the absolute value of the average
    return std::abs((fl.GetStatorCurrent() - fr.GetStatorCurrent()) / 2.0);
}

void Drivetrain::printStatus()
{
    auto const volts = getVoltage();
    auto const amps = getCurrent();
    printf("Avg Voltage: %f, Avg Current: %f\n", volts, amps);
    frc::SmartDashboard::PutNumber("Drivetrain Voltage", volts);
    frc::SmartDashboard::PutNumber("Drivetrain Amperage", amps);
}

void Drivetrain::tank(double lrate, double rrate)
{
    // Sets each motor to "PercentOutput" mode (just -100% to 100% speed, no fancy software here), and then gives the % (from -1 to 1) at which the motors should run
    fl.Set(ControlMode::PercentOutput, lrate);
    bl.Set(ControlMode::PercentOutput, lrate);
    fr.Set(ControlMode::PercentOutput, -rrate); // The right side is inverted because the motors need to turn counter-clock wise instead of CW
    br.Set(ControlMode::PercentOutput, -rrate);

/*
    if (can_shift)
    {
        double const avgVoltage = getVoltage();
        double const avgCurrent = getCurrent();
        if (shift_status == SOLENOID::SHIFT_DOWN && avgVoltage >= SOLENOID::SHIFT_UP_VOLTAGE && avgCurrent <= SOLENOID::SHIFT_UP_CURRENT)
            shift(SOLENOID::SHIFT_UP);
        else if (shift_status == SOLENOID::SHIFT_UP && (avgCurrent >= SOLENOID::SHIFT_UP_CURRENT || avgVoltage <= SOLENOID::SHIFT_DOWN_VOLTAGE))
            shift(SOLENOID::SHIFT_DOWN);
            
    } */
}

/*
void Drivetrain::shift(bool up_or_down)
{
    // shifter.Set(up_or_down);
    shift_status = up_or_down;
    printf((up_or_down == SOLENOID::SHIFT_UP) ? ("Shift!\n") : ("Unshift!\n"));
}

void Drivetrain::shift()
{
    shift_status = !shift_status;
    // shifter.Set(shift_status);
    printf((shift_status == SOLENOID::SHIFT_UP) ? ("Shift!\n") : ("Unshift!\n"));
}
*/