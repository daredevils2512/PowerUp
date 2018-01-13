#include "SetPIDEnabled.h"
#include "../Robot.h"

SetPIDEnabled::SetPIDEnabled(bool enabled) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_enabled = enabled;
}

// Called once when the command executes
void SetPIDEnabled::Initialize() {

}


void SetPIDEnabled::Execute(){
	Robot::drivetrain->SetPIDEnabled(m_enabled);
}

bool SetPIDEnabled::IsFinished(){
	return true;
}

void SetPIDEnabled::End() {

}

void SetPIDEnabled::Interrupted() {

}
