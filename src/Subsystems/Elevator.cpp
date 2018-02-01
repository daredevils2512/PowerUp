#include "Elevator.h"
#include "../RobotMap.h"

Elevator::Elevator() : Subsystem("Elevator") {

}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
bool Elevator::GetTopSwitch() {
	return RobotMap::elevatorTopSwitch->Get();
}

bool Elevator::GetBottomSwitch() {
	 return RobotMap::elevatorBottomSwitch->Get();
}

double Elevator::GetLiftEncoder() {
	return RobotMap::elevatorEncoder->Get();
}

void Elevator::ResetLiftEncoder(){
	RobotMap::elevatorEncoder->Reset();
}

void Elevator::RunLift(double speed) {
	RobotMap::elevatorLeftMotor->Set(speed);
	RobotMap::elevatorRightMotor->Set(speed);
}
