// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/TimedRobot.h>
#include "DriveTrain.hpp"

class Robot : public frc::TimedRobot
{ 
  /******************************************************************/
  /*                        Private Variables                       */
  /******************************************************************/
private:
Drivetrain drivetrain{};
public:
  /******************************************************************/
  /*                   Public Function Declarations                 */
  /******************************************************************/

  Robot();

  void RobotInit() override;
  void RobotPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;
};
