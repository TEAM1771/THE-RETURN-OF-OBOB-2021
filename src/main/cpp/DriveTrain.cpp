#include <DriveTrain.hpp>

#include <frc/Solenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <ctre/Phoenix.h>

#include <math.h>

using can_adr = unsigned int;

/******************************************************************/
/*                       Private Constants                        */
/******************************************************************/
namespace DRIVETRAIN
{
    constexpr can_adr FL_PORT = 0;
    constexpr can_adr BL_PORT = 0;
    constexpr can_adr FR_PORT = 0;
    constexpr can_adr BR_PORT = 0;
} // namespace DRIVETRAIN
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

/******************************************************************/
/*                        Private Variables                       */
/******************************************************************/

std::unique_ptr<WPI_TalonSRX> fl, fr, bl, br;

frc::Solenoid shifter{SOLENOID::PORT};

bool shift_status = SOLENOID::DEFAULT;

bool can_shift = true;

const auto talon_config = []() {
    TalonSRXConfiguration talon_config;
    talon_config.closedloopRamp = .2;
    return talon_config;
}();

/******************************************************************/
/*                  Private Function Definitions                  */
/******************************************************************/

void configTalon(std::unique_ptr<WPI_TalonSRX> &talon_srx, can_adr const &port)
{
    talon_srx = std::make_unique<WPI_TalonSRX>(port);
    talon_srx->ConfigAllSettings(talon_config);
}

[[nodiscard]] double getVoltage()
{
    return fabs((fl->GetMotorOutputVoltage() - fr->GetMotorOutputVoltage()) / 2.0);
}

[[nodiscard]] double getCurrent()
{
    return fabs((fl->GetStatorCurrent() - fr->GetStatorCurrent()) / 2.0);
}

/******************************************************************/
/*                   Public Function Definitions                  */
/******************************************************************/

void DriveTrain::init()
{
    shifter.Set(SOLENOID::DEFAULT);
    using namespace DRIVETRAIN;

    fl = std::make_unique<WPI_TalonSRX>(FL_PORT);
    bl = std::make_unique<WPI_TalonSRX>(BL_PORT);
    fr = std::make_unique<WPI_TalonSRX>(FR_PORT);
    br = std::make_unique<WPI_TalonSRX>(BR_PORT);
}

void DriveTrain::printStatus()
{
    auto const volts = getVoltage();
    auto const amps = getCurrent();
    printf("Avg Voltage: %f, Avg Current: %f\n", volts, amps);
    frc::SmartDashboard::PutNumber("Drivetrain Voltage", volts);
    frc::SmartDashboard::PutNumber("Drivetrain Amperage", amps);
}

void DriveTrain::canShift(bool shiftability)
{
    can_shift = shiftability;
    shift(SOLENOID::SHIFT_DOWN);
}

void DriveTrain::tank(double lrate, double rrate)
{

    fl->Set(ControlMode::PercentOutput, lrate);
    bl->Set(ControlMode::PercentOutput, lrate);
    fr->Set(ControlMode::PercentOutput, -rrate);
    br->Set(ControlMode::PercentOutput, -rrate);

    if (can_shift)
    {
        double const avgVoltage = getVoltage();
        double const avgCurrent = getCurrent();
        if (shift_status == SOLENOID::SHIFT_DOWN && avgVoltage >= SOLENOID::SHIFT_UP_VOLTAGE && avgCurrent <= SOLENOID::SHIFT_UP_CURRENT)
            shift(SOLENOID::SHIFT_UP);
        else if (shift_status == SOLENOID::SHIFT_UP && (avgCurrent >= SOLENOID::SHIFT_UP_CURRENT || avgVoltage <= SOLENOID::SHIFT_DOWN_VOLTAGE))
            shift(SOLENOID::SHIFT_DOWN);
    }
}

void DriveTrain::shift(bool up_or_down)
{
    shifter.Set(up_or_down);
    shift_status = up_or_down;
    printf((up_or_down == SOLENOID::SHIFT_UP) ? ("Shift!\n") : ("Unshift!\n"));
}

void DriveTrain::shift()
{
    shift_status = !shift_status;
    shifter.Set(shift_status);
    printf((shift_status == SOLENOID::SHIFT_UP) ? ("Shift!\n") : ("Unshift!\n"));
}