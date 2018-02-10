#include "ClimberRightWingRun.h"

ClimberRightWingRun::ClimberRightWingRun(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires (Robot::climber.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ClimberRightWingRun::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberRightWingRun::Execute() {
	Robot::climber->SetRightWingSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberRightWingRun::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClimberRightWingRun::End() {
	Robot::climber->SetRightWingSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberRightWingRun::Interrupted() {

}
