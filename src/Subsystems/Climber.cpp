#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber") {
LeftWingMotor1 = RobotMap::climberLeftWingMotor1;
LeftWingMotor2 = RobotMap::climberLeftWingMotor2;
RightWingMotor1 = RobotMap::climberRightWingMotor1;
RightWingMotor2 = RobotMap::climberRightWingMotor2;

}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Climber::SetWingSpeed(ClimberWing wing, double speed) {
	switch (wing){
	case ClimberWing::leftWing:
		LeftWingMotor1->Set(speed);
		LeftWingMotor2->Set(speed);
		break;
	case ClimberWing::rightWing:
		RightWingMotor1->Set(speed);
		RightWingMotor2->Set(speed);
		break;
	default:
		std::cout << "Sorry, that isn't a climber side" << std::endl;
	}

}
