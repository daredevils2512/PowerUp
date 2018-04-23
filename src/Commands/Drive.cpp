#include "Drive.h"

Drive::Drive() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());

}

// Called just before this Command runs the first time
void Drive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
	if(!Robot::drivetrain->GetAutonomous()) {
		double move = Robot::oi->GetMove();
		double turn = Robot::oi->GetTurn();
		if(Robot::elevator->GetLiftMagneticEncoder() > Util::ELEVATOR_THROTTLE_HEIGHT){
		  move *= Util::ELEVATOR_THROTTLE_AMOUNT;
		  turn *= Util::ELEVATOR_TURN_AMOUNT;
		}
		Robot::drivetrain->DriveRobotArcade(move,turn);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void Drive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {

}
