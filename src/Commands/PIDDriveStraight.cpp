#include "PIDDriveStraight.h"
#include "Robot.h"

PIDDriveStraight::PIDDriveStraight(PIDDriveStraight::PIDSettings settings, double goalDistance) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_settings = settings;
	m_distance = goalDistance;
	lastTime = 0;
	navXDistance = 0;
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
	lastTime = frc::RobotController::GetFPGATime()/1000; // last time in milliseconds
}

// Called repeatedly when this Command is scheduled to run
void PIDDriveStraight::Execute() {
	double currentTime = frc::RobotController::GetFPGATime()/1000;
	//distance traveled in time since last execution
	double tDiff = ((currentTime-lastTime)/1000);

	//TODO: fix, needs to return meters traveled since last execution in disty

	//NOTE: need to store previous velocity, possibly cause of issue
	// current code acts as if accelerated to speed from 0 --> current vel within tDiff time
	// needs to take into account previous velocity for accuracy

	double disty = sqrt( pow(RobotMap::navX->GetVelocityX() *  tDiff,2) + pow(RobotMap::navX->GetVelocityY() * tDiff,2) ) * 2;
	lastTime = currentTime; // update the last execution time

	//add meters traveled since last execution to cumulative distance
	navXDistance+=disty;

	//quarter steering control for PID to prevent crazy turns
	double output = Robot::drivetrain->GetPIDOutput()/4;

	Robot::drivetrain->DriveRobotTank(0.7-output,0.7+output); //70% besides corrections
}

// Make this return true when this Command no longer needs to run execute()
bool PIDDriveStraight::IsFinished() {
	return navXDistance >= m_distance;
}

// Called once after isFinished returns true
void PIDDriveStraight::End() {
	Robot::drivetrain->SetPIDEnabled(false);
	Robot::drivetrain->DriveRobotTank(0.0,0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PIDDriveStraight::Interrupted() {
	this->End();
}
