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

void UltrasonicSubsystem::DriveStaight(Util::RobotSide robotSide, double driveSpeed, double startDist) {
	//Function for driving the robot along a wall at any given distance using ultrasonic sensors
	//Compares both the front and back sensors, along with the starting distance away and the current distance away
	Robot::drivetrain->ResetEncoders();

	//All the doubles we using for calculations
	double frontDist = 0.0;
	double rearDist = 0.0;
	double avgDist = 0.0;
	double avgDistSlowDown = 0.0;
	double avgFrontVsRearSlowDown = 0.0;
	double avgSlowDown = 0.0;

	switch (robotSide) {
	case Util::RobotSide::leftSide:
		//Getting the distances the ultrasonic sensors are returning
		frontDist = ConvertToDistance(RobotMap::ultrasonicFrontLeft->GetVoltage());
		rearDist = ConvertToDistance(RobotMap::ultrasonicRearLeft->GetVoltage());
		avgDist = (frontDist + rearDist) / 2;

		//calculating the slow-downs
		avgDistSlowDown = GetDifference(avgDist, startDist);
		avgFrontVsRearSlowDown = GetDifference(frontDist, rearDist);
		avgSlowDown = ((avgDistSlowDown + avgFrontVsRearSlowDown) / 2) * Util::ULTRASONIC_TURN_MULTIPLIER;

		//All the cases between the two inputs
		if ((avgDist <= startDist && frontDist >= rearDist) ||
			(avgDist == startDist && frontDist == rearDist) ||
			(avgDist >= startDist && frontDist <= rearDist)) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
		} else if ((avgDist >= startDist && frontDist == rearDist) ||
				   (avgDist == startDist && frontDist >= rearDist)) {
			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed);
		} else if ((avgDist <= startDist && frontDist == rearDist) ||
				   (avgDist == startDist && frontDist <= rearDist)) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - avgSlowDown);
		} else if (avgDist >= startDist && frontDist >= rearDist) {
			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed + (avgSlowDown / 2));
		} else if (avgDist <= startDist && frontDist <= rearDist) {
			Robot::drivetrain->DriveRobotTank(driveSpeed + (avgSlowDown / 2), driveSpeed - avgSlowDown);
		} else {
			std::cout << "Something is wrong. Stopping driving" << std::endl;
			Robot::drivetrain->DriveRobotTank(0.0, 0.0);
		}
		break;
	case Util::RobotSide::rightSide:
		//Getting the distances the ultrasonic sensors are returning
//		frontDist = ConvertToDistance(RobotMap::ultrasonicFrontRight->GetVoltage());
//		rearDist = ConvertToDistance(RobotMap::ultrasonicRearRight->GetVoltage());
//		avgDist = (frontDist + rearDist) / 2;
//
//		//calculating the slow-downs
//		avgDistSlowDown = GetDifference(avgDist, startDist);
//		avgFrontVsRearSlowDown = GetDifference(frontDist, rearDist);
//		avgSlowDown = ((avgDistSlowDown + avgFrontVsRearSlowDown) / 2) * Util::ULTRASONIC_TURN_MULTIPLIER;
//
//		//All the cases between the two inputs
//		if ((avgDist <= startDist && frontDist >= rearDist) ||
//			(avgDist == startDist && frontDist == rearDist) ||
//			(avgDist >= startDist && frontDist <= rearDist)) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
//		} else if ((avgDist >= startDist && frontDist == rearDist) ||
//				   (avgDist == startDist && frontDist >= rearDist)) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - avgSlowDown);
//		} else if ((avgDist <= startDist && frontDist == rearDist) ||
//				   (avgDist == startDist && frontDist <= rearDist)) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed);
//		} else if (avgDist >= startDist && frontDist >= rearDist) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed + (avgSlowDown / 2), driveSpeed - avgSlowDown);
//		} else if (avgDist <= startDist && frontDist <= rearDist) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed + (avgSlowDown / 2));
//		} else {
//			std::cout << "Something is wrong. Stopping driving" << std::endl;
//			Robot::drivetrain->DriveRobotTank(0.0, 0.0);
//		}
		break;
	default:
		std::cout << "Sorry but that isn't an option for sides of the robot" << std::endl;
	}
}
