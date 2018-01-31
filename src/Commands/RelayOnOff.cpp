#include "RelayOnOff.h"
#include "../Robot.h"

RelayOnOff::RelayOnOff(double relayID) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_relayID = relayID;
}

// Called just before this Command runs the first time
void RelayOnOff::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RelayOnOff::Execute() {
	Robot::ultrasonicSubsystem->RelayToggle(m_relayID);
}

// Make this return true when this Command no longer needs to run execute()
bool RelayOnOff::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void RelayOnOff::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RelayOnOff::Interrupted() {

}
