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

void Climber::SetForkDirection(ForkDirection direction) {
	if (direction == ForkDirection::fDown) {
		RobotMap::climberFork->Set(frc::DoubleSolenoid::Value::kForward);
	} else {
		RobotMap::climberFork->Set(frc::DoubleSolenoid::Value::kReverse);
	}
}

void Climber::SetClawsDirection(ClawsDirection direction) {
	if (direction == ClawsDirection::cDown) {
		RobotMap::climberClaws->Set(frc::DoubleSolenoid::Value::kForward);
	} else {
		RobotMap::climberClaws->Set(frc::DoubleSolenoid::Value::kReverse);
	}
}
