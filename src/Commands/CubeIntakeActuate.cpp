#include "CubeIntakeActuate.h"

CubeIntakeActuate::CubeIntakeActuate(bool direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::cube.get());
	m_direction = direction;
}

// Called just before this Command runs the first time
void CubeIntakeActuate::Initialize() {
if (m_direction) {
	Robot::cube->ActuateIntake(frc::DoubleSolenoid::kForward);
}
else {
	Robot::cube->ActuateIntake(frc::DoubleSolenoid::kReverse);

}

}

// Called repeatedly when this Command is scheduled to run
void CubeIntakeActuate::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool CubeIntakeActuate::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CubeIntakeActuate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CubeIntakeActuate::Interrupted() {

}
