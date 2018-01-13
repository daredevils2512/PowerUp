#include "NavXSubsystem.h"
#include "../RobotMap.h"

//keep in mind for future if classdef error on constants, do this
const double NavXSubsystem::NAVX_P_VALUE = 0.03;
const double NavXSubsystem::NAVX_I_VALUE = 0.00;
const double NavXSubsystem::NAVX_D_VALUE = 0.00;
const double NavXSubsystem::NAVX_F_VALUE = 0.00;

NavXSubsystem::NavXSubsystem() : Subsystem("ExampleSubsystem") {

}

void NavXSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void NavXSubsystem::RotateToAngle(double angle) {

}
