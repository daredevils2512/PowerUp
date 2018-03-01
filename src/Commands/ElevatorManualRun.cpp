#include "ElevatorManualRun.h"
#include "../Robot.h"

ElevatorManualRun::ElevatorManualRun() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::elevator.get());
}

// Called just before this Command runs the first time
void ElevatorManualRun::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ElevatorManualRun::Execute() {
	//unless we're using the joystick, just apply a constant 5% power if higher than 3 ft
	//Doing this to correct backdriving of lift motor
	if (Robot::oi->GetLiftControl() == 0 && Robot::elevator->GetLiftMagneticEncoder() >= 0.0) { //3.1 feet
		Robot::elevator->RunLift(0.1); //0.05
	//if lift is at the top or bottom don't let it run
	} else if (Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT) {
		Robot::elevator->RunLift(0.0);
	//run off joystick
//	else if (Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT - 1.0) {
//		Robot::elevator->RunLift(Robot::oi->GetLiftControl() * (5/6));
	} else if (Robot::elevator->GetBottomSwitch() == true) {
		if (Robot::oi->GetLiftControl() > 0) {
			Robot::elevator->RunLift(Robot::oi->GetLiftControl());
		} else {
			Robot::elevator->RunLift(0.0);
		}
	} else {
		Robot::elevator->RunLift(Robot::oi->GetLiftControl());
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorManualRun::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ElevatorManualRun::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorManualRun::Interrupted() {

}
