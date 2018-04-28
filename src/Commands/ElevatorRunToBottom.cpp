/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ElevatorRunToBottom.h"
#include "../Robot.h"

ElevatorRunToBottom::ElevatorRunToBottom(double speed = -0.7, double timeout = 3.0) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	SetTimeout(timeout);
	m_speed = speed;
}

// Called just before this Command runs the first time
void ElevatorRunToBottom::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorRunToBottom::Execute() {
	Robot::elevator->RunLift(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRunToBottom::IsFinished() {
	return Robot::elevator->GetBottomSwitch() || IsTimedOut();
}

// Called once after isFinished returns true
void ElevatorRunToBottom::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRunToBottom::Interrupted() {

}
