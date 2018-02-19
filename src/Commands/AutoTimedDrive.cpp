#include "AutoTimedDrive.h"
#include "../Robot.h"

AutoTimedDrive::AutoTimedDrive(double time) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	SetTimeout(time);
}

// Called just before this Command runs the first time
void AutoTimedDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoTimedDrive::Execute() {
	Robot::drivetrain->DriveRobotArcade(-0.50, 0.0); //0.5
}

// Make this return true when this Command no longer needs to run execute()
bool AutoTimedDrive::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void AutoTimedDrive::End() {
	Robot::drivetrain->DriveRobotArcade(0.0, 0.0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTimedDrive::Interrupted() {
	End();
}
