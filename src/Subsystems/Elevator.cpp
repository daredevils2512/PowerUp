#include "Elevator.h"
#include "../Commands/ElevatorManualRun.h"
#include "../RobotMap.h"

Elevator::Elevator() :
		Subsystem("Elevator") {
//	left = RobotMap::elevatorLeftMotor;
//	right = RobotMap::elevatorRightMotor;
	motor = RobotMap::elevatorMotor;
	top = RobotMap::elevatorTopSwitch;
	bottom = RobotMap::elevatorBottomSwitch;
	encoder = RobotMap::elevatorEncoder;

}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	//SetDefaultCommand(new ElevatorManualRun());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
bool Elevator::GetTopSwitch() {
	return top->Get();
}

bool Elevator::GetBottomSwitch() {
	return bottom->Get();
}

double Elevator::GetLiftEncoder() {
	return encoder->Get();
}

void Elevator::ResetLiftEncoder() {
	return encoder->Reset();
}

void Elevator::RunLift(double speed) {
//	left->Set(speed);
//	right->Set(speed);
	motor->Set(speed);
}

double Elevator::GetLiftMagneticEncoder() {
	return RobotMap::elevatorMotor->GetSelectedSensorPosition(0) * (1/sensorUnitsPerRotation);
}
