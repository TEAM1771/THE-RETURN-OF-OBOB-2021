#include "Climber.hpp"
#include "Buttons.hpp"
#include "PID_CANSparkMax.hpp"

/******************************************************************/
/*                       Private Constants                        */
/******************************************************************/

constexpr int PORT = 17;

constexpr auto IDLE_MODE = rev::CANSparkMax::IdleMode::kBrake;

constexpr double P = 0.1771;
constexpr double I = 0.0;
constexpr double D = 0.0;

constexpr double MAX_OUTPUT = 1;

/******************************************************************/
/*                        Private Variables                       */
/******************************************************************/
inline static PID_CANSparkMax climber{PORT, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

/******************************************************************/
/*                  Private Function Definitions                  */
/******************************************************************/
void Climber::init()
{
    climber.RestoreFactoryDefaults();

    climber.SetIdleMode(IDLE_MODE);

    climber.SetP(P);
    climber.SetI(I);
    climber.SetD(D);
    // climber.SetOutputRange(-MAX_OUTPUT, MAX_OUTPUT);
    climber.SetPositionRange(-10000, 10);
    climber.SetTarget(CLIMBER::POSITION::ZERO);
    climber.SetSmartCurrentLimit(40);
}

void Climber::set(CLIMBER::POSITION position)
{
    climber.SetTarget(position, rev::ControlType::kPosition);
}

void Climber::joystickControl(double val)
{
    auto const position = climber.encoder.GetPosition();
    if (position > CLIMBER::POSITION::DOWN && val > 0)
    {
        climber.Set(0);
        return;
    }
    if (position < CLIMBER::POSITION::UP && val < 0)
    {
        climber.Set(0);
        return;
    }
    if (fabs(val) < .02)
        val = 0;
    climber.Set(val);
    printStatus();
}

void Climber::joystickControlNoLimits(double val)
{
    if (fabs(val) < .02)
        val = 0;
    climber.Set(val);
    printStatus();
}

void Climber::printStatus()
{
    std::cout << "Climber 1: " << climber.encoder.GetPosition() << std::endl;
}

void Climber::ButtonManager()
{
    if (BUTTON::CLIMBER::RAISE)
        set(CLIMBER::POSITION::UP);
    else if (BUTTON::CLIMBER::LOWER)
        set(CLIMBER::POSITION::DOWN);
}