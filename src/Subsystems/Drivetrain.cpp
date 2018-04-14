#include <cmath>
#include <algorithm>

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

    DriveTrainShift = RobotMap::drivetrainShifter;
    ChassisFront = RobotMap::drivetrainChassisFront;
    ChassisRear = RobotMap::drivetrainChassisRear;

    leftEncoder = RobotMap::drivetrainLeftEncoder;
    rightEncoder = RobotMap::drivetrainRightEncoder;

    blockJoysticks = false;

}

void Drivetrain::PIDWrite(double output) {
//	std::cout<<"Writing Drivetrain PID: " << output <<std::endl;
	pidOutput = output;
}

void Drivetrain::InitDefaultCommand() {
	SetDefaultCommand(new Drive());
}
void Drivetrain::DriveRobotArcade(double speed, double rotation) {
	//drives robot in arcade mode from specified values (TELEOP)
	ChassisFront->ArcadeDrive(speed, rotation);
	ChassisRear->ArcadeDrive(speed, rotation);
}

void Drivetrain::DriveRobotTank(double leftSpeed, double rightSpeed) {
	//Needed for the auton driving
	ChassisFront->TankDrive(leftSpeed, rightSpeed);
	ChassisRear->TankDrive(leftSpeed, rightSpeed);
}

double Drivetrain::GetLeftEncoder() {
	return leftEncoder->GetDistance();
}

double Drivetrain::GetRightEncoder() {
	return rightEncoder->GetDistance();
}

void Drivetrain::ResetEncoders() {
	leftEncoder->Reset();
	rightEncoder->Reset();
}
void Drivetrain::Shifter(frc::DoubleSolenoid::Value dir) {
	//sets the direction of the shifter solenoid
	DriveTrainShift->Set(dir);
}

void Drivetrain::SetAutonomous(bool isAutonomous) {
	blockJoysticks = isAutonomous;
}

bool Drivetrain::GetAutonomous() {
	return blockJoysticks;
}

bool Drivetrain::IsPIDEnabled() {

	return RobotMap::navXTurnController->IsEnabled();
}

void Drivetrain::SetPIDEnabled(bool enabled){
	if(enabled){
		RobotMap::navXTurnController->Enable();
	}else{
		RobotMap::navXTurnController->Disable();
	}
}

double Drivetrain::GetPIDOutput() {
//	std::cout << "Gettting drivetrain pid output: " << pidOutput << std::endl;
	if(!this->IsPIDEnabled()){
		//Util::ReportError("Accessing PID Output while PID is disabled!");
	}
	return pidOutput;
}
void Drivetrain::SetPIDSetpoint(double setpoint){
	RobotMap::navXTurnController->SetSetpoint(setpoint);
}
