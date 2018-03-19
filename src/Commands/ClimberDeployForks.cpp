/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimberDeployForks.h"
#include "../Robot.h"

ClimberDeployForks::ClimberDeployForks(Climber::ForkDirection direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_direction = direction;
}

// Called just before this Command runs the first time
void ClimberDeployForks::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberDeployForks::Execute() {
	Robot::climber->SetForkDirection(m_direction);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberDeployForks::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClimberDeployForks::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberDeployForks::Interrupted() {

}
