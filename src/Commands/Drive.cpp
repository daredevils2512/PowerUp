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
	if(!Robot::drivetrain->GetAutonomous() && Robot::elevator->GetLiftMagneticEncoder() <= 4.5) {
			std::cout << "You've been a good boy, letting you drive normally" << std::endl;
			Robot::drivetrain->DriveRobotArcade(Robot::oi->GetMove() , Robot::oi->GetTurn());
	}else if (Robot::elevator->GetLiftMagneticEncoder() > 6.5) {
		std::cout << "You're too tall! Limiting your throttle range" << std::endl;
		Robot::drivetrain->DriveRobotArcade(Robot::oi->GetMove() * 0.5 , Robot::oi->GetTurn() * 0.5);
	}else{
		Robot::drivetrain->DriveRobotArcade(Robot::oi->GetMove() , Robot::oi->GetTurn());
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
