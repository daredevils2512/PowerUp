#include "UltrasonicRelaysOff.h"
#include "../Robot.h"

UltrasonicRelaysOff::UltrasonicRelaysOff() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void UltrasonicRelaysOff::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void UltrasonicRelaysOff::Execute() {
	std::cout << "turning relays off" << std::endl;
	Robot::ultrasonicSubsystem->RelaysOff();
}

// Make this return true when this Command no longer needs to run execute()
bool UltrasonicRelaysOff::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void UltrasonicRelaysOff::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UltrasonicRelaysOff::Interrupted() {

}
