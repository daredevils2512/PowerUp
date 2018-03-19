/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ClimberPutAtAngle.h"
#include "../Robot.h"
#include "../RobotMap.h"

ClimberPutAtAngle::ClimberPutAtAngle(double angle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_angle = angle;
}

// Called just before this Command runs the first time
void ClimberPutAtAngle::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberPutAtAngle::Execute() {
	Robot::climber->SetServoAngle(m_angle, RobotMap::climbServo1.get());
	Robot::climber->SetServoAngle(m_angle, RobotMap::climbServo2.get());
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberPutAtAngle::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimberPutAtAngle::End() {
	Robot::climber->SetServoAngle(0.0, RobotMap::climbServo1.get());
	Robot::climber->SetServoAngle(0.0, RobotMap::climbServo2.get());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberPutAtAngle::Interrupted() {
	Robot::climber->SetServoAngle(0.0, RobotMap::climbServo1.get());
	Robot::climber->SetServoAngle(0.0, RobotMap::climbServo2.get());
}
