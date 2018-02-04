#ifndef UltrasonicSubsystem_H
#define UltrasonicSubsystem_H

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include "../Util.h"

class UltrasonicSubsystem : public frc::Subsystem {

private:

double lastValidFront;
double lastValidRear;

public:

enum class SensorSide {
		frontSensor,
		rearSensor
	};

double ultrasonicSaves[4] = {}; //ID 0 = thisFront value
								//ID 1 = thisRear value
								//ID 2 = lastFront value
								//ID 3 = lastrear value

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
	double m_avgSlowdown = 0.0;

	double m_lastFront;
	double m_lastRear;
	double m_thisFront;
	double m_thisRear;

	double m_avgDist = 0.0;
	double m_frontDist = 0.0;
	double m_rearDist = 0.0;


};

#endif  // UltrasonicSubsystem_H
