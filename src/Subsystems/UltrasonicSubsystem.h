#ifndef UltrasonicSubsystem_H
#define UltrasonicSubsystem_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "../Util.h"

class UltrasonicSubsystem : public frc::Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:

	UltrasonicSubsystem();
	void InitDefaultCommand();
	void ToggleRelay(int relayID);
	void RelaysOff();
	void LastValidValue(Util::RobotSide robotSide, SensorSide side, int arrayVal);
	double ConvertToDistance(double voltageMeasured);
	double GetAverageDistance(Util::RobotSide robotSide);
	double GetDifference(double frontDistance, double rearDistance);
	void DriveStaight(Util::RobotSide robotSide, double driveSpeed, double startingDistance);

	double m_startingDistance = 0.0;
};

#endif  // UltrasonicSubsystem_H
