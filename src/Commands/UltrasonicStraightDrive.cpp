#include "UltrasonicStraightDrive.h"
#include "../Subsystems/UltrasonicSubsystem.h"

UltrasonicStraightDrive::UltrasonicStraightDrive(double driveSpeed, double driveDistance, Util::RobotSide robotSide) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_driveSpeed = driveSpeed;
	m_driveDistance = driveDistance;
	m_robotSide = robotSide;
}

// Called just before this Command runs the first time
void UltrasonicStraightDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void UltrasonicStraightDrive::Execute() {
	Robot::ultrasonicSubsystem->DriveStaight(m_robotSide, m_driveSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool UltrasonicStraightDrive::IsFinished() {
	return ((Robot::drivetrain->GetLeftEncoder() + Robot::drivetrain->GetRightEncoder()) / 2) >= m_driveDistance;
}

// Called once after isFinished returns true
void UltrasonicStraightDrive::End() {
	Robot::drivetrain->DriveRobotTank(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UltrasonicStraightDrive::Interrupted() {
	Robot::drivetrain->DriveRobotTank(0.0, 0.0);
}
