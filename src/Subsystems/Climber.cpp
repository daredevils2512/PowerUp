#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber") {

}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Climber::SetClimbSpeed(double speed) {
	RobotMap::climber->Set(speed);
}

void Climber::SetServoPos(double pos, Servo * name) {
	//0.0 = full left
	//1.0 = full right
	name->Set(pos);
}

void Climber::SetServoAngle(double angle, Servo * name) {
	name->SetAngle(angle);
}

double Climber::GetServoPos(Servo * name) {
	//0.0 = full left
	//1.0 = full right
	return(name->Get());
}

double Climber::GetServoAngle(Servo * name) {
	return(name->GetAngle());
}

void Climber::SetForkDirection(ForkDirection direction) {
	if (direction == ForkDirection::down) {
		RobotMap::climberFork->Set(frc::DoubleSolenoid::Value::kForward);
	} else {
		RobotMap::climberFork->Set(frc::DoubleSolenoid::Value::kReverse);
	}
}
