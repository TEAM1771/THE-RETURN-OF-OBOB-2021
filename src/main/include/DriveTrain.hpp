#pragma once

/******************************************************************/
/*                  Public Function Declarations                  */
/******************************************************************/
namespace DriveTrain
{
    void init();
    void tank(double lrate, double rrate);

    void shift(bool toshift);
    void shift();

    void canShift(bool status);

    void printVelocity();
} // namespace DriveTrain