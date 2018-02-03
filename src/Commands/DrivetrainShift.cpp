#include "DrivetrainShift.h"
#include "Robot.h"

DrivetrainShift::DrivetrainShift() {
	Requires(Robot::drivetrain.get());
}

void DrivetrainShift::Initialize() {
	SetInterruptible(false);
//	SetTimeout(0.02);
	//stops the drivetrain
//	Robot::drivetrain->DriveRobotArcade(0.0 , 0.0);
}

void DrivetrainShift::Execute() {
	RobotMap::drivetrainShifter->Set(currentStatus);
}

bool DrivetrainShift::IsFinished() {
	return true; //IsTimedOut()
}

void DrivetrainShift::End() {
	currentStatus = DoubleSolenoid::kOff;
}

void DrivetrainShift::Interrupted() {
	End();
}
