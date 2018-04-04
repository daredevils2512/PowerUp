/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimberRunDeploy.h"
#include "Robot.h"

ClimberRunDeploy::ClimberRunDeploy(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::climber.get());
	m_deploy = speed;
}

// Called just before this Command runs the first time
void ClimberRunDeploy::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberRunDeploy::Execute() {
	Robot::climber->SetDeploySpeed(m_deploy);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberRunDeploy::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimberRunDeploy::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberRunDeploy::Interrupted() {

}
