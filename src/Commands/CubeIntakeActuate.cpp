#include "CubeIntakeActuate.h"

CubeIntakeActuate::CubeIntakeActuate() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::cube.get());
}

// Called repeatedly when this Command is scheduled to run
void CubeIntakeActuate::Execute() {
	Robot::cube->ActuateIntake(this->getDirection());
}

// Make this return true when this Command no longer needs to run execute()
bool CubeIntakeActuate::IsFinished() {
	return true;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CubeIntakeActuate::Interrupted() {

}
