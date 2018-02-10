#include "UltrasonicSubsystem.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Util.h"
#include "../Commands/CMG_UltrasonicRelaySwitching.h"


#include <cmath>

UltrasonicSubsystem::UltrasonicSubsystem() : Subsystem("UltrasonicSubsystem") {

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
	/* NOT FOR USE WHILE ENABLED
	 * This function returns an invalid value while the robot is enabled due
	 * to the ultrasonic sensors being toggled on and off which causes one of
	 * the values to be zero at all times
	 */

	double frontDistance = 0.0;
	double rearDistance = 0.0;
	switch (robotSide) {
	case Util::RobotSide::leftSide:
		frontDistance = RobotMap::ultrasonicFrontLeft->GetDistance();
		rearDistance = RobotMap::ultrasonicRearLeft->GetDistance();
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
	double avgDistSlowDown = 0.0;
	double avgFrontVsRearSlowDown = 0.0;
	double m_avgSlowDown = 0.0;
	m_startingDistance = startDist * 2;

	switch (robotSide) {
	case Util::RobotSide::leftSide:
		//Getting the distances the ultrasonic sensors are returning

		frontDist = RobotMap::ultrasonicFrontLeft->GetDistance();
		rearDist = RobotMap::ultrasonicRearLeft->GetDistance();
		avgDist = (frontDist + rearDist) / 2;


		m_frontDist = m_thisFront + m_lastFront;
		m_rearDist = m_thisRear + m_lastRear;

//		m_frontDist = Robot::ultrasonicSubsystem->lastValidFront;
//		m_rearDist = Robot::ultrasonicSubsystem->lastValidRear;

//		m_frontDist = ConvertToDistance(RobotMap::ultrasonicFrontLeft->GetVoltage()); //proven to work //switch to GetAverageVoltage
//		m_rearDist = ConvertToDistance(RobotMap::ultrasonicRearLeft->GetVoltage());
		m_avgDist = (m_frontDist + m_rearDist) / 2;

		std::cout << "Front dist: " << m_frontDist << std::endl;
		std::cout << "Rear dist: " << m_rearDist << std::endl;
		std::cout << "Avg Dist: " << m_avgDist << std::endl;
		//calculating the slow-downs
		avgDistSlowDown = GetDifference(m_avgDist, m_startingDistance);
		avgFrontVsRearSlowDown = GetDifference(m_frontDist, m_rearDist);
		m_avgSlowDown = ((avgDistSlowDown + avgFrontVsRearSlowDown) / 2) * Util::ULTRASONIC_TURN_MULTIPLIER;
		std::cout << "Slowdown Speed: " << m_avgSlowDown << std::endl;

		//All the cases between the two inputs
		if ((m_avgDist <= m_startingDistance && m_frontDist >= m_rearDist) ||
			(m_avgDist >= m_startingDistance && m_frontDist <= m_rearDist) ||
			(Util::IsInTolerance(Util::ULTRASONIC_ANGLE_TOLERANCE, m_frontDist, m_rearDist) &&
			 Util::IsInTolerance(Util::ULTRASONIC_DISTANCE_TOLERANCE, m_avgDist, m_startingDistance))) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
			std::cout << "Driving Straight" << std::endl;
		} else if ((avgDist > startDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, frontDist, rearDist)) ||
				   (frontDist > rearDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, avgDist, startDist))) {
			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - avgSlowDown); //flip-flopped with right slow turn
			std::cout << "Turning Left Gradually" << std::endl;
		} else if ((avgDist < startDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, frontDist, rearDist)) ||
				   (frontDist > rearDist && Util::IsInTolerance(Util::ULTRASONIC_TOLERANCE, avgDist, startDist))) {
			Robot::drivetrain->DriveRobotTank(driveSpeed - avgSlowDown, driveSpeed);
			std::cout << "Turning Right Gradually" << std::endl;
		} else if (avgDist > startDist && frontDist >= rearDist) {
			Robot::drivetrain->DriveRobotTank(driveSpeed + (avgSlowDown / 2), driveSpeed - avgSlowDown); //flip-flopped with right turn wuick
			std::cout << "Turning Left Quickly" << std::endl;
		} else if (avgDist < startDist && frontDist <= rearDist) {
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
//		m_frontDist = ConvertToDistance(RobotMap::ultrasonicFrontRight->GetVoltage());
//		m_rearDist = ConvertToDistance(RobotMap::ultrasonicRearRight->GetVoltage());
//		m_avgDist = (m_frontDist + m_rearDist) / 2;
//
//		//calculating the slow-downs
//		avgDistSlowDown = GetDifference(m_avgDist, m_startingDistance);
//		avgFrontVsRearSlowDown = GetDifference(m_frontDist, m_rearDist);
//		m_avgSlowDown = ((avgDistSlowDown + avgFrontVsRearSlowDown) / 2) * Util::ULTRASONIC_TURN_MULTIPLIER;
//
//		//All the cases between the two inputs
//		if ((m_avgDist <= m_startingDistance && m_frontDist >= m_rearDist) ||
//			(m_avgDist == m_startingDistance && m_frontDist == m_rearDist) ||
//			(m_avgDist >= m_startingDistance && m_frontDist <= m_rearDist)) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed);
//		} else if ((m_avgDist >= m_startingDistance && m_frontDist == m_rearDist) ||
//				   (m_avgDist == m_startingDistance && m_frontDist >= m_rearDist)) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed, driveSpeed - m_avgSlowDown);
//		} else if ((m_avgDist <= m_startingDistance && m_frontDist == m_rearDist) ||
//				   (m_avgDist == m_startingDistance && m_frontDist <= m_rearDist)) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed - m_avgSlowDown, driveSpeed);
//		} else if (m_avgDist >= m_startingDistance && m_frontDist >= m_rearDist) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed + (m_avgSlowDown / 2), driveSpeed - m_avgSlowDown);
//		} else if (m_avgDist <= m_startingDistance && m_frontDist <= m_rearDist) {
//			Robot::drivetrain->DriveRobotTank(driveSpeed - m_avgSlowDown, driveSpeed + (m_avgSlowDown / 2));
//		} else {
//			std::cout << "Something is wrong. Stopping driving" << std::endl;
//			Robot::drivetrain->DriveRobotTank(0.0, 0.0);
//		}
		break;
	default:
		std::cout << "Sorry but that isn't an option for sides of the roobt" << std::endl;
	}
}
