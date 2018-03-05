/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "CubeSwitchCheck.h"
#include "Robot.h"

CubeSwitchCheck::CubeSwitchCheck() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::cube.get());
}

// Called just before this Command runs the first time
void CubeSwitchCheck::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CubeSwitchCheck::Execute() {
	if (Robot::cube->GetLimitSwitch()) {
		Robot::cube->SetIntakeSpeed(0.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CubeSwitchCheck::IsFinished() {
	std::cout << "Limit status: " << Robot::cube->GetLimitSwitch() << std::endl;
//	return Robot::cube->GetLimitSwitch();
	return true;
}

// Called once after isFinished returns true
void CubeSwitchCheck::End() {
	Robot::cube->SetIntakeSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CubeSwitchCheck::Interrupted() {

}
