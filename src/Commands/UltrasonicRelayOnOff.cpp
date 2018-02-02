#include <Commands/UltrasonicRelayOnOff.h>
#include "../Robot.h"

UltrasonicRelayOnOff::UltrasonicRelayOnOff(double relayID) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_relayID = relayID;
}

// Called just before this Command runs the first time
void UltrasonicRelayOnOff::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void UltrasonicRelayOnOff::Execute() {
	Robot::ultrasonicSubsystem->ToggleRelay(m_relayID);
}

// Make this return true when this Command no longer needs to run execute()
bool UltrasonicRelayOnOff::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void UltrasonicRelayOnOff::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UltrasonicRelayOnOff::Interrupted() {

}
