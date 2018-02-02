#include "UltrasonicStoreLastValue.h"

UltrasonicStoreLastValue::UltrasonicStoreLastValue(UltrasonicSubsystem::SensorSide side) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::ultrasonicSubsystem.get());
	//m_valid = lastValid;
	m_side = side;

}

// Called just before this Command runs the first time
void UltrasonicStoreLastValue::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void UltrasonicStoreLastValue::Execute() {
	Robot::ultrasonicSubsystem->LastValidValue(m_side);
}

// Make this return true when this Command no longer needs to run execute()
bool UltrasonicStoreLastValue::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void UltrasonicStoreLastValue::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UltrasonicStoreLastValue::Interrupted() {

}
