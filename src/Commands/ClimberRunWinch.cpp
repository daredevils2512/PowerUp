/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimberRunWinch.h"
#include "../Robot.h"

ClimberRunWinch::ClimberRunWinch(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ClimberRunWinch::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberRunWinch::Execute() {
	Robot::climber->SetClimbSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberRunWinch::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimberRunWinch::End() {
	Robot::climber->SetClimbSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberRunWinch::Interrupted() {
	Robot::climber->SetClimbSpeed(0.0);
}
