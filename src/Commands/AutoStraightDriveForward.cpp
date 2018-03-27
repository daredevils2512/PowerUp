#include <Commands/AutoStraightDriveForward.h>
#include "../Robot.h"
#include "../Subsystems/Drivetrain.h"

AutoStraightDriveForward::AutoStraightDriveForward(double targetFeet, double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	//FORWARD IS NEGATIVE
	m_targetFeet = targetFeet;
	m_speed = -1.0 * (fabs(speed)); //abs returns an integer which messed with driving logic, float absolute value works though
	//setting a timeout in case it doesn't move so it doesn't keep trying forever
	SetTimeout(2.5);
}

// Called just before this Command runs the first time
void AutoStraightDriveForward::Initialize() {
	//reseting the encoders before we start
	Robot::drivetrain->ResetEncoders();
	std::cout << "drive started" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void AutoStraightDriveForward::Execute() {
	//drives the robot using tank drive so each side drives the same
	Robot::drivetrain->DriveRobotTank(m_speed, m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoStraightDriveForward::IsFinished() {
	//determines if the robot is done driving based off of encoders or if it timed out
	double leftDistance = abs(Robot::drivetrain->GetLeftEncoder());
	double rightDistance = abs(Robot::drivetrain->GetRightEncoder());
	if(fabs(leftDistance - rightDistance) > 6) {
		//set lagging encoder to value of other encoder
		if(leftDistance > rightDistance) {
			rightDistance = leftDistance;
		}else{
			leftDistance = rightDistance;
		}
	}
	if(IsTimedOut()) {
		std::cout << "timed out" << std::endl;
	}
	return ((rightDistance + leftDistance) / 2) >= m_targetFeet || IsTimedOut();
}

// Called once after isFinished returns true
void AutoStraightDriveForward::End() {
	//turns off the motors when we're done
	std::cout << "drive completed" << std::endl;
	Robot::drivetrain->DriveRobotTank(0.0 , 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoStraightDriveForward::Interrupted() {

}
