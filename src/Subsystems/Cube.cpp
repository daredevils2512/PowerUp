#include <Subsystems/Cube.h>
#include "../RobotMap.h"

Cube::Cube() : Subsystem("Cube") {
intakeLeft = RobotMap::cubeIntakeLeftMotor;
intakeRight = RobotMap::cubeIntakeRightMotor;
cubeIntakeSolenoid = RobotMap::cubeIntakeSolenoid;
}

void Cube::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Cube::SetIntakeSpeed(double speed) {
	intakeLeft->Set(speed);
	intakeRight->Set(speed);
}

void Cube::ActuateIntake(frc::DoubleSolenoid::Value direction) {
	cubeIntakeSolenoid->Set(direction);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
