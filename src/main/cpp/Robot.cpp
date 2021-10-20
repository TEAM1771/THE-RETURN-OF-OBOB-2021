// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"


void Robot::RobotInit() {}
void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic()
{
  double left = BUTTON::ps5leftJoy.GetX();
  if (fabs(left) < .1)
    left = 0;
  double right = -BUTTON::ps5rightJoy.GetY();
  if (fabs(right) < .1)
    right = 0;
  
/*  double rotate = BUTTON::ps5.GetZ() * 2;
  if(fabs(rotate) < .1)
    rotate = 0;
*/
  driveTrain.tank(left, right);

}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
