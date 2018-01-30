#include "RelayOnOff.h"
#include "../RobotMap.h"

RelayOnOff::RelayOnOff() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RelayOnOff::Initialize() {
	m_currentState = RobotMap::ultrasonicRelay1->Get();
}

// Called repeatedly when this Command is scheduled to run
void RelayOnOff::Execute() {
	if (m_currentState) {
		RobotMap::ultrasonicRelay1->Set(false);
		RobotMap::ultrasonicRelay2->Set(false);
		RobotMap::ultrasonicRelay3->Set(false);
		RobotMap::ultrasonicRelay4->Set(false);
	} else {
		RobotMap::ultrasonicRelay1->Set(true);
		RobotMap::ultrasonicRelay2->Set(true);
		RobotMap::ultrasonicRelay3->Set(true);
		RobotMap::ultrasonicRelay4->Set(true);
	}
	m_currentState = RobotMap::ultrasonicRelay1->Get();
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
