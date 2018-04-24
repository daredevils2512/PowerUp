#include <Subsystems/Cube.h>
#include "../RobotMap.h"

Cube::Cube() : Subsystem("Cube") {
intakeLeft = RobotMap::cubeIntakeLeftMotor;
intakeRight = RobotMap::cubeIntakeRightMotor;
intakeSolenoid = RobotMap::cubeIntakeSolenoid;
limitSwitch = RobotMap::cubeIntakeLimitSwitch;
intakeDeploy = RobotMap::cubeDeploySolenoid;
}

void Cube::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Cube::SetIntakeSpeed(double speed) {
#ifdef Alea
	intakeLeft->Set(speed *-1); //Alea
	intakeRight->Set(speed); //Alea
#else
	intakeLeft->Set(speed * -1); //Atlas
	intakeRight->Set(speed * -1); //Atlas
#endif
}

void Cube::ActuateIntake(frc::DoubleSolenoid::Value direction) {
	intakeSolenoid->Set(direction);
}

void Cube::ActuateDeploy(frc::DoubleSolenoid::Value direction) {
	intakeDeploy->Set(direction);
}

bool Cube::GetLimitSwitch() {
	return (limitSwitch->Get() ? true : false);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
