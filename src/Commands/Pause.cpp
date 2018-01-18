#include "Pause.h"

Pause::Pause(double time) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	SetTimeout(time);
}

// Called just before this Command runs the first time
void Pause::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Pause::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool Pause::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void Pause::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Pause::Interrupted() {

}
