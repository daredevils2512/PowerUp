#include "ElevatorSafety.h"
#include "../Robot.h"

ElevatorSafety::ElevatorSafety() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::elevator.get());

	shouldFix = false;
	done = false;
}

// Called just before this Command runs the first time
void ElevatorSafety::Initialize() {
	shouldFix = !Robot::elevator->GetBottomSwitch();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorSafety::Execute() {
	if(shouldFix){
		Robot::elevator->RunLift(-0.4);
		done = Robot::elevator->GetBottomSwitch();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorSafety::IsFinished() {
	return !shouldFix || done;
}

// Called once after isFinished returns true
void ElevatorSafety::End() {
	Robot::elevator->RunLift(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorSafety::Interrupted() {
	this->End();
}
