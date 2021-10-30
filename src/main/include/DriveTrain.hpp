#pragma once

#include <math.h>

#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>


#include <Transmission.hpp>

namespace DRIVETRAIN {
    namespace LTRANS {
        constexpr int MTRA = 15;
        constexpr int MTRB = 16;

        constexpr int ENCA = 0;
        constexpr int ENCB = 1;
    }

    namespace RTRANS {
        constexpr int MTRA = 14;
        constexpr int MTRB = 17;

        constexpr int ENCA = 2;
        constexpr int ENCB = 3;
    }


    namespace SOLENOID{
        constexpr int PORT = 0;

        constexpr bool SHIFT_UP = true;
        constexpr bool SHIFT_DOWN = !SHIFT_UP;
        constexpr bool DEFAULT = SHIFT_DOWN;

        constexpr int SHIFT_UP_SPEED = 15000; // 2900 in 2016
        constexpr int SHIFT_DOWN_SPEED = 14000; // 2200 in 2016
    }
}

class DriveTrain {
public:
    DriveTrain();
    void tank(double lrate, double rrate);

    void shift(bool toshift);
    void shift();

    void canShift(bool status);

    void printVelocity();

    void update();

private:

    // Transmission<ctre::phoenix::motorcontrol::can::TalonFX> ltrm{{
    // // Transmission<WPI_TalonSRX> ltrm{{
    //     {DRIVETRAIN::LTRANS::MTRA, Direction::Reverse}, 
    //     {DRIVETRAIN::LTRANS::MTRB, Direction::Forward}
    // }, {DRIVETRAIN::LTRANS::ENCA, DRIVETRAIN::LTRANS::ENCB} }, 
    // rtrm{{
    //     {DRIVETRAIN::RTRANS::MTRA, Direction::Forward},
    //     {DRIVETRAIN::RTRANS::MTRB, Direction::Forward}
    // }, {DRIVETRAIN::RTRANS::ENCA, DRIVETRAIN::RTRANS::ENCB} };

    ctre::phoenix::motorcontrol::can::TalonFX
        r1 { DRIVETRAIN::RTRANS::MTRA },
        r2 { DRIVETRAIN::RTRANS::MTRB },
        l1 { DRIVETRAIN::LTRANS::MTRA },
        l2 { DRIVETRAIN::LTRANS::MTRB };


    frc::Solenoid shifter{DRIVETRAIN::SOLENOID::PORT};

    bool shift_status = DRIVETRAIN::SOLENOID::DEFAULT;
    bool can_shift = true;
};