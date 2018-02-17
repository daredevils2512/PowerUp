/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "PrintCurrentFPGATime.h"
#include <WPILib.h>
#include <iostream>

PrintCurrentFPGATime::PrintCurrentFPGATime() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void PrintCurrentFPGATime::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void PrintCurrentFPGATime::Execute() {
	std::cout << "Current Time: " << frc::RobotController::GetFPGATime()/1000000.0 << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool PrintCurrentFPGATime::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void PrintCurrentFPGATime::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PrintCurrentFPGATime::Interrupted() {

}
