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
	//EXPERIMENTAL, if the joystick position is above a certain value and it's been long enough
	//since our last gear shift then let the drivetrain shift into high gear
	if (fabs(Robot::oi->GetMove() > m_shiftThreshold) && (m_currentTime - m_lastShiftTime) > m_shiftTimeThreshold){
		Util::ReportWarning("Shifting up because you're slow");
		Robot::drivetrain->Shifter(frc::DoubleSolenoid::kForward); //shift into high gear
		m_lastShiftTime = m_currentTime;
	}else{
		Util::ReportWarning("Shifting down because you suck");
		Robot::drivetrain->Shifter(frc::DoubleSolenoid::kReverse); //drop into low gear
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
