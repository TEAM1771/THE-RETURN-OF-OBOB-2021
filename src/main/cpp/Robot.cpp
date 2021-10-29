// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"
#include <thread>
#include "Constants.hpp"

void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  driveTrain.tank(.5, .5);
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(1s);
  driveTrain.tank(0, 0);
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic()
{
  double const left = BUTTON::JOY1.GetY();
  double const right = BUTTON::JOY2.GetY();

  driveTrain.tank(left, right);
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
