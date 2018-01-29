#include "CubeExtakeActuate.h"

CubeExtakeActuate::CubeExtakeActuate(bool direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::cube.get());
	m_direction = direction;
}

// Called just before this Command runs the first time
void CubeExtakeActuate::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CubeExtakeActuate::Execute() {
	if (m_direction) {
		Robot::cube->ActuateExtake(frc::DoubleSolenoid::kForward);
	}
	else {
		Robot::cube->ActuateExtake(frc::DoubleSolenoid::kReverse);

	}

}

// Make this return true when this Command no longer needs to run execute()
bool CubeExtakeActuate::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CubeExtakeActuate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CubeExtakeActuate::Interrupted() {

}
