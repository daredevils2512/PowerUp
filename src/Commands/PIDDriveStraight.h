#ifndef PIDDriveStraight_H
#define PIDDriveStraight_H

#include "WPILib.h"

class PIDDriveStraight : public frc::Command {
public:
	 enum class PIDSettings {
		CARPET90
	};

	PIDDriveStraight(double goalDistance, double timeout = 5.0, double speed = 0.70, PIDSettings settings = PIDSettings::CARPET90);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	PIDSettings m_settings;
	double m_distance;
	bool m_reverse;
	double navXDistance;
	long lastTime;
	double lastVelX;
	double lastVelY;
	long lastTimeDiff;
	long cumlTime;
	double m_speed;
};

#endif  // PIDDriveStraight_H
