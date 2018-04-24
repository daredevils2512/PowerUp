/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CubeIntakeDeploy.h"

CubeIntakeDeploy::CubeIntakeDeploy(bool direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::cube.get());
	m_direction = direction;
}

// Called just before this Command runs the first time
void CubeIntakeDeploy::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CubeIntakeDeploy::Execute() {
if (m_direction) {
	Robot::cube->ActuateDeploy(frc::DoubleSolenoid::kForward);
}else{
	Robot::cube->ActuateDeploy(frc::DoubleSolenoid::kReverse);
}

}

// Make this return true when this Command no longer needs to run execute()
bool CubeIntakeDeploy::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CubeIntakeDeploy::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CubeIntakeDeploy::Interrupted() {

}
