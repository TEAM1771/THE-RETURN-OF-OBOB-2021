// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"
#include <thread>
#include "Buttons.hpp"
// #include "Climber.hpp" Climber is broken as of Spring 2022

/******************************************************************/
/*                   Public Function Definitions                  */
/******************************************************************/

Robot::Robot()
{
  BUTTON::JOY1.SetTwistChannel(5);
}

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  drivetrain.tank(-.3, -.3);
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(6s);
  drivetrain.tank(0, 0);

  // Drives backwards at 30% speed for 6 seconds, then stops
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic()
{
  // double const left = BUTTON::JOY1.GetY();
  // double const right = BUTTON::JOY1.GetTwist();

  // drivetrain.tank(left, right);
  // drivetrain.printStatus();

  if(BUTTON::TRIANGLE)
  {
    drivetrain.tank(1,1);
  }
  else
  {
    drivetrain.tank(0,0);
  }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

/******************************************************************/
/*                  Private Function Definitions                  */
/******************************************************************/
#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
