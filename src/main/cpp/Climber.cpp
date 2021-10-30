#include "Climber.hpp"
#include "Constants.hpp"

//static (private) variables
inline static PID_CANSparkMax climber{CLIMBER::PORT_1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
//inline static auto encoder = climber.GetEncoder();

//function definitions
void Climber::init()
{
    climber.RestoreFactoryDefaults();

    climber.SetIdleMode(CLIMBER::IDLE_MODE);

    climber.SetP(CLIMBER::P);
    climber.SetI(CLIMBER::I);
    climber.SetD(CLIMBER::D);
    // climber.SetOutputRange(-CLIMBER::MAX_OUTPUT, CLIMBER::MAX_OUTPUT);
    climber.SetPositionRange(-10000, 10);
    climber.SetTarget(CLIMBER::POSITION::ZERO);
    climber.SetSmartCurrentLimit(40);

    //    climber_2.SetP(CLIMBER::P);
    //    climber_2.SetI(CLIMBER::I);
    //    climber_2.SetD(CLIMBER::D);
    //    climber_2.SetOutputRange(-CLIMBER::MAX_OUTPUT, CLIMBER::MAX_OUTPUT);
    //    climber_2.SetPositionRange(-CLIMBER::POSITION::UP, CLIMBER::POSITION::ZERO);
    //    climber_2.SetTarget(CLIMBER::POSITION::ZERO);
}

void Climber::set(CLIMBER::POSITION position)
{
    climber.SetTarget(position, rev::ControlType::kPosition);
    //    climber_2.SetTarget(-position, rev::ControlType::kPosition);
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
    //    climber_2.Set(-val);
    printStatus();
}

void Climber::joystickControlNoLimits(double val)
{
    if (fabs(val) < .02)
        val = 0;
    climber.Set(val);
    //    climber_2.Set(-val);
    printStatus();
}

void Climber::printStatus()
{
    std::cout << "Climber 1: " << climber.encoder.GetPosition() << std::endl;
    //    std::cout << "Climber 2: " << climber_2.encoder.GetPosition() << std::endl;
}

void Climber::ButtonManager()
{
    if (BUTTON::CLIMBER::RAISE)
        set(CLIMBER::POSITION::UP);
    else if (BUTTON::CLIMBER::LOWER)
        set(CLIMBER::POSITION::DOWN);
}