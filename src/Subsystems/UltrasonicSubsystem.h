#ifndef UltrasonicSubsystem_H
#define UltrasonicSubsystem_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "../Util.h"
#include <string>

class UltrasonicSubsystem : public frc::Subsystem {

private:

double lastValidFront = 0.0;
double lastValidRear= 0.0;
double currentFrontDistance = 0.0;
double currentRearDistance = 0.0;

public:

enum class SensorSide {
		frontSensor,
		rearSensor
	};

	UltrasonicSubsystem();
	void InitDefaultCommand();
	void ToggleRelay(int relayID);
	void RelaysOff();
	void LastValidValue (SensorSide side);
	double ConvertToDistance(double voltageMeasured);
	double GetAverageDistance(Util::RobotSide robotSide);
	double GetDifference(double frontDistance, double rearDistance);
	void DriveStaight(Util::RobotSide robotSide, double driveSpeed, double startingDistance);

	double m_startingDistance = 0.0;


};

#endif  // UltrasonicSubsystem_H
