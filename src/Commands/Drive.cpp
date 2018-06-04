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
	//AUTOMATIC SHIFTER
	//check to see if joystick is at zero and we are currently in high gear -- SHIFT INTO LOW GEAR
	//check to make sure joystick value is over 80% and we're over the max encoder rate for the gear we're in -- SHIFT INTO HIGH
//	if (Robot::drivetrain->GetShifter() == DoubleSolenoid::kForward && fabs(Robot::oi->GetMove()) == 0.0
//		&& (fabs(RobotMap::drivetrainLeftEncoder->GetRate()) + fabs(RobotMap::drivetrainRightEncoder->GetRate())) / 2 < m_HighGearShiftDown ) {
//		Util::ReportWarning("Shifting into low");
//		Robot::drivetrain->Shifter(frc::DoubleSolenoid::kReverse);
//	} else if
//		(Robot::drivetrain->GetShifter() == DoubleSolenoid::kReverse && fabs(Robot::oi->GetMove()) >= m_shiftThreshold
//		&& (fabs(RobotMap::drivetrainLeftEncoder->GetRate()) + fabs(RobotMap::drivetrainRightEncoder->GetRate())) / 2 >= m_lowGearRate * m_encoderShiftThreshold ) {
//		Util::ReportWarning("Shifting into high");
//		Robot::drivetrain->Shifter(frc::DoubleSolenoid::kForward);
//	}
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
