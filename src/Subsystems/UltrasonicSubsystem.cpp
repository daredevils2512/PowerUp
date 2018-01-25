#include "UltrasonicSubsystem.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Util.h"

UltrasonicSubsystem::UltrasonicSubsystem() : Subsystem("ExampleSubsystem") {
	std::cout << "Constructed ultrasonic subsystem" << std::endl;
}

void UltrasonicSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double UltrasonicSubsystem::ConvertToDistance(double voltageMeasured) {
	double voltagePerCm = 0.0;
	double distanceCm = 0.0;
	double distanceInches = 0.0;
	voltagePerCm = Util::SUPPLIED_VOLTAGE/1024;
	distanceCm = voltageMeasured/voltagePerCm;
	distanceInches = distanceCm/2.54;
	return distanceInches;
}

double UltrasonicSubsystem::GetDifference(double frontDistance, double rearDistance){
	return abs(frontDistance - rearDistance);
}

double UltrasonicSubsystem::GetAverageDistance(Util::RobotSide robotSide) {
	double frontDistance = 0.0;
	double rearDistance = 0.0;
	switch (robotSide) {
	case Util::RobotSide::leftSide:
		frontDistance = ConvertToDistance(RobotMap::ultrasonicFrontLeft->GetVoltage());
		rearDistance = ConvertToDistance(RobotMap::ultrasonicRearLeft->GetVoltage());
		break;
	case Util::RobotSide::rightSide:
		break;
	default:
		std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
	}
	return (frontDistance + rearDistance) / 2;
}

void UltrasonicSubsystem::DriveStaight(Util::RobotSide robotSide, double driveSpeed, double startingDistance) {
	Robot::drivetrain->ResetEncoders();
	double frontDistance = 0.0;
	double rearDistance = 0.0;
	double turnSlowDown = 0.0;
	double currentAvgDistance = 0.0;
	switch (robotSide) {
	case Util::RobotSide::leftSide:
		frontDistance = ConvertToDistance(RobotMap::ultrasonicFrontLeft->GetVoltage());
		rearDistance = ConvertToDistance(RobotMap::ultrasonicRearLeft->GetVoltage());
		break;
	case Util::RobotSide::rightSide:
//		frontDistance = GetDistance(RobotMap::ultrasonicFrontRight->GetVoltage());
//		rearDistance = GetDistance(RobotMap::ultrasonicRearRight->GetVoltage());
		break;
	default:
		std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
	}

	currentAvgDistance = (frontDistance + rearDistance) / 2;
	turnSlowDown = GetDifference(frontDistance, rearDistance) * Util::ULTRASONIC_TURN_MULTIPLIER;
	std::cout << "Slowdown thing: " << turnSlowDown << std::endl;

//	if (Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, frontDistance, rearDistance)) {
//		Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
//	} else {
//		if (frontDistance > rearDistance) {
//			switch (robotSide) {
//			case Util::RobotSide::leftSide:
//				Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - turnSlowDown);
//				break;
//			case Util::RobotSide::rightSide:
//				Robot::drivetrain->DriveRobotTank(driveSpeed - turnSlowDown, driveSpeed);
//				break;
//			default:
//				std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
//			}
//		} else if (rearDistance > frontDistance) {
//			switch (robotSide) {
//			case Util::RobotSide::leftSide:
//				Robot::drivetrain->DriveRobotTank(driveSpeed - turnSlowDown, driveSpeed);
//				break;
//			case Util::RobotSide::rightSide:
//				Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - turnSlowDown);
//				break;
//			default:
//				std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
//			}
//		} else {
//			std::cout << "Something is wrong, check the ultrasonic sensors" << std::endl;
//		}
//	}
	if (Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, currentAvgDistance, startingDistance)) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
		} else {
			if (currentAvgDistance > startingDistance) {
				switch (robotSide) {
				case Util::RobotSide::leftSide:
					Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - turnSlowDown);
					break;
				case Util::RobotSide::rightSide:
					Robot::drivetrain->DriveRobotTank(driveSpeed - turnSlowDown, driveSpeed);
					break;
				default:
					std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
				}
			} else if (startingDistance > currentAvgDistance) {
				switch (robotSide) {
				case Util::RobotSide::leftSide:
					Robot::drivetrain->DriveRobotTank(driveSpeed - turnSlowDown, driveSpeed);
					break;
				case Util::RobotSide::rightSide:
					Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - turnSlowDown);
					break;
				default:
					std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
				}
			} else {
				std::cout << "Something is wrong, check the ultrasonic sensors" << std::endl;
			}
		}
}
