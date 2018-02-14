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
	double ConvertToDistance(double voltageMeasured);
	double GetAverageDistance(Util::RobotSide robotSide);
	double GetDifference(double frontDistance, double rearDistance);
	void DriveStaight(Util::RobotSide robotSide, double driveSpeed, double startingDistance);

	double m_startingDistance = 0.0;
	bool m_turnLeftGradual = false;
	bool m_turnLeftQuigly = false;
	bool m_turnRightGradual = false;
	bool m_turnRightQuigly = false;
	bool m_staright = false;
};

#endif  // UltrasonicSubsystem_H
