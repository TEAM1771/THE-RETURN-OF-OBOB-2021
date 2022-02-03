#include <DriveTrain.hpp>

#include <frc/PowerDistributionPanel.h>
#include <frc/Solenoid.h>

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

    constexpr int SHIFT_UP_SPEED = 15000;   // 2900 in 2016
    constexpr int SHIFT_DOWN_SPEED = 14000; // 2200 in 2016
} // namespace SOLENOID

/******************************************************************/
/*                        Private Variables                       */
/******************************************************************/

frc::PowerDistributionPanel PDH{};

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

[[nodiscard]] double getVelocity()
{
    return fabs((fl->GetSelectedSensorVelocity() - fr->GetSelectedSensorVelocity()) / 2.0);
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

void DriveTrain::printVelocity()
{
    printf("Avg Vel: %f\n", getVelocity);
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
        double const avgVelocity = getVelocity();
        if (shift_status == SOLENOID::SHIFT_DOWN && avgVelocity >= SOLENOID::SHIFT_UP_SPEED)
            shift(SOLENOID::SHIFT_UP);
        else if (shift_status == SOLENOID::SHIFT_UP && avgVelocity <= SOLENOID::SHIFT_DOWN_SPEED)
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