#include <cmath>

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

    DriveTrainShift = RobotMap::drivetrainShifter;
    Chassis = RobotMap::drivetrainChassis;
    blockJoysticks = false;

}

void Drivetrain::InitDefaultCommand() {

}
void Drivetrain::DriveRobotArcade(double speed, double rotation) {
	//drives robot in arcade mode from specified values (TELEOP)
	Chassis->ArcadeDrive(speed, rotation);
}

void Drivetrain::DriveRobotTank(double leftSpeed, double rightSpeed) {
	//Needed for the auton driving
	Chassis->TankDrive(leftSpeed, rightSpeed);
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
