// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"
#include <thread>
#include "Constants.hpp"
#include "Climber.hpp"

void Robot::RobotInit()
{
  Climber::init();
}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit()
{
  driveTrain.tank(-.3, -.3);
  using namespace std::literals::chrono_literals;
  std::this_thread::sleep_for(6s);
  driveTrain.tank(0, 0);
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic()
{
  // if (BUTTON::CLIMBER::RAISE)
  // {
  //   Climber::joystickControl(BUTTON::JOY2.GetY());
  // }
  // else
  // {
  // Climber::joystickControl(0);
  double const left = BUTTON::JOY1.GetY();
  double const right = BUTTON::JOY2.GetY();

  driveTrain.tank(left, right);
  //Climber::printStatus();
  Climber::ButtonManager();
  driveTrain.printVelocity();
  // }
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic()
{
  Climber::printStatus();
}

void Robot::TestInit() {}
void Robot::TestPeriodic()
{
  Climber::joystickControlNoLimits(BUTTON::JOY2.GetY());
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
