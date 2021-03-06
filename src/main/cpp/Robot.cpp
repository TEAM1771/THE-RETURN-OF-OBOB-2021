// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"
#include <thread>
#include "Buttons.hpp"
#include "Climber.hpp"

/******************************************************************/
/*                   Public Function Definitions                  */
/******************************************************************/
void Robot::RobotInit()
{
  Climber::init();
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  drivetrain.tank(-.3, -.3);
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(6s);
  drivetrain.tank(0, 0);
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic()
{
  // if (BUTTON::CLIMBER::RAISE)
  //   Climber::joystickControl(BUTTON::JOY2.GetY());
  // else
  // Climber::joystickControl(0);
  double const left = BUTTON::JOY1.GetY();
  double const right = BUTTON::JOY2.GetY();

  drivetrain.tank(left, right);
  //Climber::printStatus();
  Climber::ButtonManager();
  // drivetrain.printStatus();
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic()
{
  // Climber::printStatus();
}

void Robot::TestInit() {}
void Robot::TestPeriodic()
{
  Climber::printStatus();
  Climber::joystickControlNoLimits(BUTTON::JOY2.GetY());
}

/******************************************************************/
/*                  Private Function Definitions                  */
/******************************************************************/
#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
