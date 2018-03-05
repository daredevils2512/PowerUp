#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber") {
leftMotor = RobotMap::climberLeftWingMotor;
rightMotor = RobotMap::climberRightWingMotor;

}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Climber::SetWingSpeed(ClimberWing wing, double speed) {
	switch (wing){
	case ClimberWing::leftWing:
		leftMotor->Set(speed);
		break;
	case ClimberWing::rightWing:
		rightMotor->Set(speed);
		break;
	default:
		std::cout << "Sorry, that isn't a climber side" << std::endl;
	}

}
