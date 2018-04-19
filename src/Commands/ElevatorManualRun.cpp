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
	//unless we're using the joystick, just apply a constant 10% power
	//Doing this to correct backdriving of lift motor
	if (Robot::oi->GetLiftControl() == 0 && Robot::elevator->GetLiftMagneticEncoder() >= 0.0) { //3.1 feet
		Robot::elevator->RunLift(0.1); //0.05

	//if lift is at the top don't let it run up any farther
	} else if ((Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT) && (Robot::oi->GetLiftControl() < 0)) {
		Robot::elevator->RunLift(Robot::oi->GetLiftControl());

	//if lift is at the bottom don't let it run any farther down
	} else if (Robot::elevator->GetBottomSwitch() && (Robot::oi->GetLiftControl() > 0)) {
		Robot::elevator->RunLift(Robot::oi->GetLiftControl());

	//if we are trying to run down faster than 3/4 speed slow it down to max of 3/4
	} else if (Robot::oi->GetLiftControl() < -0.75) {
		Robot::elevator->RunLift(Robot::oi->GetLiftControl() * 0.75); //0.5

	//run lift off of joystick
	} else if (Robot::oi->GetLiftControl() != 0) {
		Robot::elevator->RunLift(Robot::oi->GetLiftControl());

	//else don't run lift cause no bueno
	} else if (Robot::elevator->GetBottomSwitch() || (Robot::elevator->GetLiftMagneticEncoder() >= Util::ELEVATOR_MAX_ENCODER_HEIGHT)) {
		Robot::elevator->RunLift(0.0);
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
