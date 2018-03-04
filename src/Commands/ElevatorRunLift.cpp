#include "ElevatorRunLift.h"

ElevatorRunLift::ElevatorRunLift(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	//Requires(Robot::elevator.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ElevatorRunLift::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorRunLift::Execute() {
	if (Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT) {
		Robot::elevator->RunLift(0.0);
	} else if (Robot::elevator->GetBottomSwitch() == true) {
		Robot::elevator->RunLift(0.0);
	}
//	else if (Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT - 1.0) {
//		Robot::elevator->RunLift(m_speed * (5/6));
//	}
	else {
		Robot::elevator->RunLift(m_speed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRunLift::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ElevatorRunLift::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRunLift::Interrupted() {
	Robot::elevator->RunLift(0.0);
}
