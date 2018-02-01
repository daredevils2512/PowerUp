#include "ElevatorManualRun.h"
#include "../Robot.h"

ElevatorManualRun::ElevatorManualRun() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void ElevatorManualRun::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorManualRun::Execute() {
	Robot::elevator->RunLift(Robot::oi->GetLiftControl());
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorManualRun::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ElevatorManualRun::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorManualRun::Interrupted() {

}
