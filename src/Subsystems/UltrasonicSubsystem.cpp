#include "UltrasonicSubsystem.h"
#include "UltrasonicPIDSource.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Util.h"

UltrasonicSubsystem::UltrasonicSubsystem() : Subsystem("ExampleSubsystem") {
//	RobotMap::ultrasonicTurnController->SetSetpoint(0);
	std::cout << "Constructed ultrasonic subsystem" << std::endl;
}

void UltrasonicSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void UltrasonicSubsystem::PIDWrite(double output) {
//	std::cout << "Writing ultrasonic PID output: " << output << std::endl;
	pidOutput = output;
}

double UltrasonicSubsystem::GetPIDOutput() {
	if (!this->IsPIDEnabled()) {
		Util::ReportError("Accessing PID Output while PID is disabled!");
	}
	return pidOutput;
}

bool UltrasonicSubsystem::IsPIDEnabled() {
//	std::cout << "CHecking if PID is enabled" << std::endl;
	return RobotMap::ultrasonicTurnController->IsEnabled();
}

void UltrasonicSubsystem::SetPIDEnabled(bool enabled) {
	if(enabled){
		RobotMap::ultrasonicTurnController->Enable();
//		std::cout << "PID Enabled for ultrasonic" << std::endl;
	}else{
		RobotMap::ultrasonicTurnController->Disable();
//		std::cout <<"PID Disabled for ultrasonic" << std::endl;
	}
}

double UltrasonicSubsystem::GetDistance(double voltageMeasured) {
	double voltagePerCm = 0.0;
	double distanceCm = 0.0;
	double distanceInches = 0.0;
	voltagePerCm = Util::SUPPLIED_VOLTAGE/1024;
	distanceCm = voltageMeasured/voltagePerCm;
	distanceInches = distanceCm/2.54;
	return distanceInches;
}

void UltrasonicSubsystem::DriveStaight(Util::RobotSide robotSide, double driveSpeed) {
	Robot::drivetrain->ResetEncoders();
	SetPIDEnabled(true);
	double frontDistance = 0.0;
	double rearDistance = 0.0;
	switch (robotSide) {
	case Util::RobotSide::leftSide:
		Robot::ultrasonicPidSource->SetRobotSide(Util::RobotSide::leftSide);
		frontDistance = GetDistance(RobotMap::ultrasonicFrontLeft->GetVoltage());
		rearDistance = GetDistance(RobotMap::ultrasonicRearLeft->GetVoltage());
		break;
	case Util::RobotSide::rightSide:
		Robot::ultrasonicPidSource->SetRobotSide(Util::RobotSide::rightSide);
//		frontDistance = GetDistance(RobotMap::ultrasonicFrontRight->GetVoltage());
//		rearDistance = GetDistance(RobotMap::ultrasonicRearRight->GetVoltage());
		break;
	default:
		std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;

	}
	if (IsPIDEnabled()) {
		double turnSlowdown = GetPIDOutput();
		double turnSpeedup = turnSlowdown/2;
		std::cout << "PID output : " << turnSlowdown << std::endl;
		if (frontDistance > rearDistance) {
			switch (robotSide) {
			case Util::RobotSide::leftSide:
				Robot::drivetrain->DriveRobotTank(driveSpeed+turnSpeedup, driveSpeed-turnSlowdown);
				break;
			case Util::RobotSide::rightSide:
				Robot::drivetrain->DriveRobotTank(driveSpeed-turnSlowdown, driveSpeed+turnSpeedup);
				break;
			default:
				std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
			}
		} else if (rearDistance > frontDistance) {
			switch (robotSide) {
			case Util::RobotSide::leftSide:
				Robot::drivetrain->DriveRobotTank(driveSpeed-turnSlowdown, driveSpeed+turnSpeedup);
				break;
			case Util::RobotSide::rightSide:
				Robot::drivetrain->DriveRobotTank(driveSpeed+turnSpeedup, driveSpeed-turnSlowdown);
				break;
			default:
				std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
			}
		} else {
			std::cout << "Something is wrong, check the ultrasonic sensors" << std::endl;
		}
	}
}
