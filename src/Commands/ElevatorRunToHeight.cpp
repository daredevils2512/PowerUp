#include <Commands/ElevatorRunToHeight.h>
#include "../Robot.h"

ElevatorRunToHeight::ElevatorRunToHeight(double speed, double encPos) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
	m_speed = speed;
	m_encPos = encPos;
}

// Called just before this Command runs the first time
void ElevatorRunToHeight::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorRunToHeight::Execute() {
	Robot::elevator->RunLift(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRunToHeight::IsFinished() {
	return (Robot::elevator->GetLiftMagneticEncoder() >= m_encPos) || //GetLiftEncoder
			Robot::elevator->GetTopSwitch() 			   ||
			Robot::elevator->GetBottomSwitch();
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
