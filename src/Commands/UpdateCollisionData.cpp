/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "UpdateCollisionData.h"
#include "../Robot.h"

UpdateCollisionData::UpdateCollisionData() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::navXSubsystem.get());
}

// Called just before this Command runs the first time
void UpdateCollisionData::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void UpdateCollisionData::Execute() {
	Robot::navXSubsystem->UpdateCollisionData(Robot::navXSubsystem->xData.name);
	Robot::navXSubsystem->UpdateCollisionData(Robot::navXSubsystem->yData.name);
	Robot::navXSubsystem->UpdateCollisionData(Robot::navXSubsystem->zData.name);

}

// Make this return true when this Command no longer needs to run execute()
bool UpdateCollisionData::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void UpdateCollisionData::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpdateCollisionData::Interrupted() {

}
