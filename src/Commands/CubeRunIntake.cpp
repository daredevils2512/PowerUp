#include "CubeRunIntake.h"

CubeRunIntake::CubeRunIntake(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires (Robot::cube.get());
	m_speed = speed;
}

CubeRunIntake::CubeRunIntake(double speed, double timeout){
	Requires (Robot::cube.get());
	m_speed = speed;
	SetTimeout(timeout);
}

// Called just before this Command runs the first time
void CubeRunIntake::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CubeRunIntake::Execute() {
	if (Robot::cube->GetLimitSwitch() == true) {
		if (m_speed >= 0) {
			Robot::cube->SetIntakeSpeed(0.0);
		} else {
			Robot::cube->SetIntakeSpeed(m_speed);
		}
	} else {
		Robot::cube->SetIntakeSpeed(m_speed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool CubeRunIntake::IsFinished() {
	return Robot::cube->GetLimitSwitch() && m_speed >= 0 || IsTimedOut();
}

// Called once after isFinished returns true
void CubeRunIntake::End() {
	Robot::cube->SetIntakeSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CubeRunIntake::Interrupted() {

}
