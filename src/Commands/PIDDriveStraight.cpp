#include "PIDDriveStraight.h"
#include "Robot.h"

PIDDriveStraight::PIDDriveStraight(double goalDistance, double timeout, PIDDriveStraight::PIDSettings settings) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	SetTimeout(timeout);
	m_settings = settings;
	// GOAL DISTANCE IS IN INCHES
	if(goalDistance < 0){
		m_distance = goalDistance;
		m_reverse = true;
	}else{
		m_distance = (goalDistance) - 12;
		m_reverse = false;
	}
	lastTime = 0;
	navXDistance = 0;
	lastVelX = 0;
	lastVelY = 0;
	lastTimeDiff=0;
	cumlTime=0;
}


// Called just before this Command runs the first time
void PIDDriveStraight::Initialize() {
	navXDistance = 0;
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
		case PIDSettings::CARPET90: // settings known to work well for 90 deg turns on carpet
			PVal = 0.055;
			IVal = 0.00001;
			DVal = 0.045;
			FVal = 0.00;
			break;
	}
	//reset nav x values so they can be worked with w/ pid
	RobotMap::navX->Reset();
	RobotMap::navX->ResetDisplacement();

	//apply pid
	RobotMap::navXTurnController->SetPID(PVal, IVal, DVal, FVal);
	Robot::drivetrain->SetPIDSetpoint(0);
	Robot::drivetrain->SetPIDEnabled(true);

	Robot::drivetrain->ResetEncoders();

	//lastTime = frc::RobotController::GetFPGATime()/1000; // last time in milliseconds
	//cumlTime = 0;
}

// Called repeatedly when this Command is scheduled to run
void PIDDriveStraight::Execute() {
	//quarter steering control for PID to prevent crazy turns*/
	double output = Robot::drivetrain->GetPIDOutput()/2;
	if(m_reverse){
		Robot::drivetrain->DriveRobotTank(0.7+output,0.7-output);
	}else{
		Robot::drivetrain->DriveRobotTank(-0.7-output,-0.7+output); //80% besides corrections //0.6
	}
}

// Make this return true when this Command no longer needs to run execute()
bool PIDDriveStraight::IsFinished() {
	//get average encoder distance in inches, compare to mdist (scaled to feet)
	//return Robot::drivetrain->GetLeftEncoder() /*( ( Robot::drivetrain->GetLeftEncoder() + Robot::drivetrain->GetRightEncoder() )/2 )*/ >= m_distance;
	return (abs((Robot::drivetrain->GetLeftEncoder() + Robot::drivetrain->GetRightEncoder()) /2) >= m_distance) ||
			IsTimedOut();
}

// Called once after isFinished returns true
void PIDDriveStraight::End() {
	Robot::drivetrain->SetPIDEnabled(false);
	Robot::drivetrain->DriveRobotTank(0.0,0.0);
	std::cout << "encoder @  end: " << Robot::drivetrain->GetLeftEncoder() << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDDriveStraight::Interrupted() {
	this->End();
}
