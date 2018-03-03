#include <Commands/ElevatorRunToHeight.h>
#include "../Robot.h"

ElevatorRunToHeight::ElevatorRunToHeight(double speed, double encPos) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	m_speed = speed;
	m_encPos = encPos;
	m_runDown = false;
}

// Called just before this Command runs the first time
void ElevatorRunToHeight::Initialize() {
	m_runDown = Robot::elevator->GetLiftMagneticEncoder() > m_encPos;
}

// Called repeatedly when this Command is scheduled to run
void ElevatorRunToHeight::Execute() {
	if (Robot::elevator->GetLiftMagneticEncoder() <= m_encPos) {
		Robot::elevator->RunLift(m_speed);
	} else if (Robot::elevator->GetLiftMagneticEncoder() >= m_encPos) {
		Robot::elevator->RunLift(-0.5);
	}
//	else if (Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT - 1.0) {
//		Robot::elevator->RunLift(m_speed * (5/6));
//	}
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRunToHeight::IsFinished() {
	return (Util::IsInTolerance(0.08, Robot::elevator->GetLiftMagneticEncoder(), m_encPos) ||
			Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT ||
			Robot::elevator->GetLiftMagneticEncoder() < 0 ||
			(Robot::elevator->GetBottomSwitch() && m_runDown) ) ;
}

// Called once after isFinished returns true
void ElevatorRunToHeight::End() {
	Robot::elevator->RunLift(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRunToHeight::Interrupted() {
	Robot::elevator->RunLift(0.0);
}
