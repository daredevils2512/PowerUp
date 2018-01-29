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

	//All the doubles we using for calculations
	double frontDist = 0.0;
	double rearDist = 0.0;
	double avgDist = 0.0;
	double avgDistSlowDown = 0.0;
	double avgFrontVsRearSlowDown = 0.0;
	double avgSlowDown = 0.0;
	m_startingDistance = startDist;

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
		std::cout << "Slowdown Speed: " << avgSlowDown << std::endl;

		//All the cases between the two inputs
		if ((avgDist <= startDist && frontDist >= rearDist) ||
			(avgDist >= startDist && frontDist <= rearDist) ||
			(Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, frontDist, rearDist) &&
			 Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, avgDist, startDist))) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
			std::cout << "Driving Straight" << std::endl;
		} else if ((avgDist >= startDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, frontDist, rearDist)) ||
				   (frontDist >= rearDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, avgDist, startDist))) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - avgSlowDown); //flip-flopped with right slow turn
			std::cout << "Turning Left Gradually" << std::endl;
		} else if ((avgDist <= startDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, frontDist, rearDist)) ||
				   (frontDist <= rearDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, avgDist, startDist))) {
			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed);
			std::cout << "Turning Right Gradually" << std::endl;
		} else if (avgDist >= startDist && frontDist >= rearDist) {
			Robot::drivetrain->DriveRobotTank(driveSpeed + (avgSlowDown / 2), driveSpeed - avgSlowDown); //flip-flopped with right turn wuick
			std::cout << "Turning Left Quickly" << std::endl;
		} else if (avgDist <= startDist && frontDist <= rearDist) {
			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed + (avgSlowDown / 2));
			std::cout << "Turning Right Quickly" << std::endl;
		} else {
			std::cout << "Something is wrong. Stopping driving" << std::endl;
			Robot::drivetrain->DriveRobotTank(0.0, 0.0);
		}
		break;
	case Util::RobotSide::rightSide:
		//will comment back in once we have 2 sensors on the right side

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
