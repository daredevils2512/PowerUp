#include "DrivetrainShift.h"
#include "Robot.h"

DrivetrainShift::DrivetrainShift(bool Direction) {
	Requires(Robot::drivetrain.get());
	m_Direction = Direction;
}

void DrivetrainShift::Initialize() {
	SetInterruptible(false);
	SetTimeout(0.02);
	//stops the drivetrain
	Robot::drivetrain->DriveRobotArcade(0.0 , 0.0);
}

void DrivetrainShift::Execute() {
if (m_Direction) {
	Robot::drivetrain->Shifter(DoubleSolenoid::kForward);
}
else {
	Robot::drivetrain->Shifter(DoubleSolenoid::kReverse);
}

}

bool DrivetrainShift::IsFinished() {
	return IsTimedOut();
}

void DrivetrainShift::End() {

}

void DrivetrainShift::Interrupted() {
	End();
}
