#include "ElevatorRunLift.h"

ElevatorRunLift::ElevatorRunLift(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ElevatorRunLift::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorRunLift::Execute() {
	Robot::elevator->RunLift(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRunLift::IsFinished() {
//	if (Robot::elevator->GetTopSwitch() || Robot::elevator->GetBottomSwitch() ||
//			Robot::elevator->GetLiftEncoder() >= Util::ELEVATOR_MAX_ENCODER_CLICKS) {
//		End();
//	}
	//TODO comment back in once limit switches are added on
	return true;
}

// Called once after isFinished returns true
void ElevatorRunLift::End() {
	Robot::elevator->RunLift(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRunLift::Interrupted() {
	Robot::elevator->RunLift(0.0);
}
