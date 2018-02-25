#include <Subsystems/Cube.h>
#include "../RobotMap.h"

Cube::Cube() : Subsystem("Cube") {
intakeLeft = RobotMap::cubeIntakeLeftMotor;
intakeRight = RobotMap::cubeIntakeRightMotor;
intakeSolenoid = RobotMap::cubeIntakeSolenoid;
grabSolenoid = RobotMap::cubeIntakeGrabberSolenoid;
limitSwitch = RobotMap::cubeIntakeLimitSwitch;
}

void Cube::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Cube::SetIntakeSpeed(double speed) {
	intakeLeft->Set(speed); //TODO make inverted on Alea
	intakeRight->Set(speed);
}

void Cube::ActuateIntake(frc::DoubleSolenoid::Value direction) {
	intakeSolenoid->Set(direction);
}

void Cube::ActuateGrabber(frc::DoubleSolenoid::Value direction) {
	grabSolenoid->Set(direction);
}

bool Cube::GetLimitSwitch() {
	if (limitSwitch->Get()) {
		return true;
	}else{
		return false;
	}
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
