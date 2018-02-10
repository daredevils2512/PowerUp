#include "Commands/ClimberRunWing.h"

ClimberRunWing::ClimberRunWing(Climber::ClimberWing wing, double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires (Robot::climber.get());
	m_speed = speed;
	m_wing = wing;
}

// Called just before this Command runs the first time
void ClimberRunWing::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberRunWing::Execute() {
	Robot::climber->SetWingSpeed(m_wing, m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberRunWing::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClimberRunWing::End() {
	Robot::climber->SetWingSpeed(m_wing, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberRunWing::Interrupted() {

}
