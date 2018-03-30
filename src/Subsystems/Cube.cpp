#include <Subsystems/Cube.h>
#include "../RobotMap.h"

Cube::Cube() : Subsystem("Cube") {
intakeLeft = RobotMap::cubeIntakeLeftMotor;
intakeRight = RobotMap::cubeIntakeRightMotor;
intakeSolenoid = RobotMap::cubeIntakeSolenoid;
limitSwitch = RobotMap::cubeIntakeLimitSwitch;
}

void Cube::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Cube::SetIntakeSpeed(double speed) {
	//TODO change these directions for the mini apple loss regional
	intakeLeft->Set(speed *-1); //Alea
//	intakeLeft->Set(speed * -1); //Atlas
	intakeRight->Set(speed); //Alea
//	intakeRight->Set(speed * -1); //Atlas
}

void Cube::ActuateIntake(frc::DoubleSolenoid::Value direction) {
	intakeSolenoid->Set(direction);
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
