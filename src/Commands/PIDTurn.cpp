#include "PIDTurn.h"
#include "Robot.h"
#include <algorithm>

/****
 * TODO: TEST, COMMAND IS UNTESTED AND EXPERIMENTAL
 ****/

PIDTurn::PIDTurn(PIDTurn::PIDSettings settings, double goalAngle) {
	// Use Requires() here to declare subsystem dependencies
	// eg.
	Requires(Robot::drivetrain.get());
	m_settings = settings;
	m_angle = goalAngle;
}

PIDTurn::PIDTurn(double goalAngle){
	Requires(Robot::drivetrain.get());
	m_settings = PIDSettings::CARPET90;
	m_angle = goalAngle;
}

// Called just before this Command runs the first time
void PIDTurn::Initialize() {
	/*
	 * Carpet 90 *
		 P: 0.055
		 I: 0.00001
		 D: 0.045
		 F: 0.00
	 */
	double PVal = 0.055;
	double IVal = 0.00001;
	double DVal = 0.045;
	double FVal = 0.00;
	switch(m_settings){
		case PIDSettings::CARPET90:
			PVal = 0.055;
			IVal = 0.00001;
			DVal = 0.045;
			FVal = 0.00;
			break;
	}
	//reset navX, set pid values, activate pid
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();
	RobotMap::navXTurnController->SetPID(PVal, IVal, DVal, FVal);
	Robot::drivetrain->SetPIDSetpoint(m_angle);
	Robot::drivetrain->SetPIDEnabled(true);
}

// Called repeatedly when this Command is scheduled to run
void PIDTurn::Execute() {

	//apply pid values to motors to turn robot (dime spin)
	double maxOutput = 0.7; //0.75 //0.70
	double output = std::max(-maxOutput,std::min(maxOutput,Robot::drivetrain->GetPIDOutput()));
	Robot::drivetrain->DriveRobotTank(-output,output);
}

// Make this return true when this Command no longer needs to run execute()
bool PIDTurn::IsFinished() {
	//PIDGet returns yaw, or whatever implementation now represents
	//Turn robot until acceptance threshold met (0.5 deg)
	return abs(m_angle - Robot::navxPidSource->PIDGet()) <= 0.5;
}

// Called once after isFinished returns true
void PIDTurn::End() {
	Robot::drivetrain->SetPIDEnabled(false);
	Robot::drivetrain->DriveRobotTank(0,0);
	std::cout<< "ENDED " << m_angle << " DEG TURN END AT " << RobotMap::navX->GetYaw() << " (" << ( m_angle-RobotMap::navX->GetYaw() ) << " DEG OFF)"<<std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDTurn::Interrupted() {
	this->End();
}
