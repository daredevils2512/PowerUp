#include "SetPIDSetpoint.h"

#include "../Robot.h"

SetPIDSetpoint::SetPIDSetpoint(double setpoint) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_setpoint = setpoint;
}

// Called just before this Command runs the first time
void SetPIDSetpoint::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SetPIDSetpoint::Execute() {
	Robot::drivetrain->SetPIDSetpoint(m_setpoint);
}

// Make this return true when this Command no longer needs to run execute()
bool SetPIDSetpoint::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetPIDSetpoint::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetPIDSetpoint::Interrupted() {

}
