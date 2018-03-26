/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimberUseClaws.h"
#include "../Robot.h"

ClimberUseClaws::ClimberUseClaws(Climber::ClawsDirection direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_direction = direction;
}

// Called just before this Command runs the first time
void ClimberUseClaws::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberUseClaws::Execute() {
	Robot::climber->SetClawsDirection(m_direction);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberUseClaws::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClimberUseClaws::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberUseClaws::Interrupted() {

}
