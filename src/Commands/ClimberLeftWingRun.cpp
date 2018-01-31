#include "ClimberLeftWingRun.h"

ClimberLeftWingRun::ClimberLeftWingRun(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires (Robot::climber.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ClimberLeftWingRun::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberLeftWingRun::Execute() {
	Robot::climber->SetLeftWingSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberLeftWingRun::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClimberLeftWingRun::End() {
	Robot::climber->SetLeftWingSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberLeftWingRun::Interrupted() {

}
