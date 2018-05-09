#include "Elevator.h"
#include "../Commands/ElevatorManualRun.h"
#include "../RobotMap.h"
#include "../Robot.h"

Elevator::Elevator() :	Subsystem("Elevator") {
	motor = RobotMap::elevatorMotor;
	bottom = RobotMap::elevatorBottomSwitch;
	backmotor = RobotMap::elevatorBackMotor;
}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new ElevatorManualRun());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Elevator::GetBottomSwitch() {
	return bottom->Get();
}

void Elevator::RunLift(double speed) {
	motor->Set(speed);
	backmotor->Set(speed);
}

double Elevator::GetLiftMagneticEncoder() {
	return -RobotMap::elevatorMotor->GetSelectedSensorPosition(0)* (1 / sensorUnitsPerRotation); //this returns it in feet
}

double Elevator::ResetMagneticEncoder() {
	return RobotMap::elevatorMotor->SetSelectedSensorPosition(0, 0, 0);
}
