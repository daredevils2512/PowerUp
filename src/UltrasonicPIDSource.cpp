/*
 * UltrasonicPIDSource.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: noahg
 */

#include "UltrasonicPIDSource.h"
#include "RobotMap.h"
#include "Robot.h"

UltrasonicPIDSource::UltrasonicPIDSource() {
	std::cout << "Constructed the ultrasonicPIDSource" << std::endl;
}

void UltrasonicPIDSource::SetRobotSide(Util::RobotSide robotSide) {
	m_robotSide = robotSide;
}

UltrasonicPIDSource::~UltrasonicPIDSource() {
	// TODO Auto-generated constructor stub

}

PIDSourceType UltrasonicPIDSource::GetPIDSourceType() const {
	return this->m_pidSource;
}

double UltrasonicPIDSource::PIDGet() {
	std::cout << "Getting PID" << std::endl;
	switch (m_robotSide) {
	case (Util::RobotSide::leftSide):
		frontDistance = Robot::ultrasonicSubsystem->GetDistance(RobotMap::ultrasonicFrontLeft->GetAverageVoltage());
		rearDistance = Robot::ultrasonicSubsystem->GetDistance(RobotMap::ultrasonicRearLeft->GetAverageVoltage());
		break;
	case (Util::RobotSide::rightSide):
		frontDistance = Robot::ultrasonicSubsystem->GetDistance(RobotMap::ultrasonicFrontLeft->GetAverageVoltage());
		rearDistance = Robot::ultrasonicSubsystem->GetDistance(RobotMap::ultrasonicRearLeft->GetAverageVoltage());
		break;
	}
	return (frontDistance - rearDistance);
}

void UltrasonicPIDSource::SetPIDSourceType(PIDSourceType pidSource) {
	m_pidSource = pidSource;
}
