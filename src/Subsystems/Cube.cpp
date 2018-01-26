#include <Subsystems/Cube.h>
#include "../RobotMap.h"

Cube::Cube() : Subsystem("Cube") {
intakeMotor1 = RobotMap::motor1;
intakeMotor2 = RobotMap::motor2;
intakeMotor3 = RobotMap::motor3;
intakeMotor4 = RobotMap::motor4;
extakeMotor = RobotMap::motor5;
cubeIntakeSolenoid = RobotMap::cubeIntakeSolenoid;
cubeExtakeSolenoid = RobotMap::cubeExtakeSolenoid;

}

void Cube::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Cube::SetIntakeSpeed(double speed) {
	intakeMotor1->Set(-speed * 0.6667);
	intakeMotor2->Set(-speed);
	intakeMotor3->Set(speed * 0.6667);
	intakeMotor4->Set(speed);
}

void Cube::SetExtakeSpeed(double speed) {
	extakeMotor->Set(speed);
}

void Cube::ActuateIntake(frc::DoubleSolenoid::Value direction) {
	cubeIntakeSolenoid->Set(direction);
}

void Cube::ActuateExtake(frc::DoubleSolenoid::Value direction) {
	cubeExtakeSolenoid->Set(direction);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
